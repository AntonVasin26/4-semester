#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <chrono>

#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/containers/pair.hpp>

class Chat
{
private:

    using shared_memory_t = boost::interprocess::managed_shared_memory;
    using manager_t = shared_memory_t::segment_manager;
    using string_allocator_t = boost::interprocess::allocator <char, manager_t>;
    using string_t = boost::interprocess::basic_string <char, std::char_traits <char>, string_allocator_t>;
    using pair = boost::interprocess::pair <string_t, string_t>;
    using deque_allocator_t = boost::interprocess::allocator <pair, manager_t>;
    using deque_t = boost::interprocess::deque <pair, deque_allocator_t>;
    using mutex_t = boost::interprocess::interprocess_mutex;
    using condition_t = boost::interprocess::interprocess_condition;
    using counter_t = std::atomic < std::size_t >;

public:

    Chat(const std::string& user_name, const std::string& chat_name) : m_user_name(user_name), m_exit_flag(false), shared_memory_name(chat_name)
    {
        m_shared_memory = shared_memory_t(boost::interprocess::open_or_create, shared_memory_name.c_str(), 4096);

        m_deque = m_shared_memory.find_or_construct < deque_t >(deque_name.c_str())(m_shared_memory.get_segment_manager());
        m_mutex = m_shared_memory.find_or_construct < mutex_t >(mutex_name.c_str())();
        m_condition = m_shared_memory.find_or_construct < condition_t >(condition_name.c_str())();
        m_users = m_shared_memory.find_or_construct < counter_t >(users_name.c_str())(0);
        count_delete_messeages = m_shared_memory.find_or_construct < counter_t >(messages_name.c_str())(0);
        vector_size = m_shared_memory.find_or_construct < counter_t >(vector_size_name.c_str())(0);


        (*m_users)++;
    }

    ~Chat() noexcept = default;

public:

    void run()
    {
        auto reader = std::thread(&Chat::read, this);

        write();

        reader.join();

        send_message(" left the chat");

        if (!(--(*m_users)))
        {
            boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
        }
    }

private:

    void read()
    {
        send_message(" joined the chat");

        while (true)
        {
            std::unique_lock lock(*m_mutex);
            m_condition->wait(lock, [this]() { return !m_deque->empty() && (m_exit_flag || m_local_messages != *vector_size); });

            if (m_exit_flag)
            {
                break;
            }

            while (*vector_size != m_local_messages)
            {
                auto message = (*m_deque)[m_local_messages - *count_delete_messeages];
                std::cout << message.first << ": " << message.second << std::endl;
                m_local_messages++;
            }
        }
    }

    void show_history()
    {
        std::scoped_lock lock(*m_mutex);

        std::cout << "history: \n";

        for (const auto& message : *m_deque)
        {
            std::cout << message.first << ": " << message.second << std::endl;
        }

        std::cout << "history end \n";
    }

    void send_message(const std::string& message)
    {
        boost::interprocess::scoped_lock lock(*m_mutex);
        string_t un(m_user_name.c_str(), m_shared_memory.get_segment_manager());
        string_t ms(message.c_str(), m_shared_memory.get_segment_manager());
        m_deque->push_back(pair(un, ms));
        (*vector_size)++;


        if (m_deque->size() > 10)
        {
            *count_delete_messeages += 5;
            auto b = m_deque->begin();
            m_deque->erase(b, b + 5);
        }

        m_condition->notify_all();

        if (message == "exit")
        {
            m_exit_flag = true;
        }

        m_local_messages++;
    }

    void write()
    {
        std::string message;

        while (!m_exit_flag)
        {
            std::getline(std::cin, message);

            if (message == "//show history")  show_history();

            else send_message(message);

        }
    }

private:

    static inline const std::string size_vec_flag = "vector cleared";
    static inline const std::string deque_name = "vector";
    static inline const std::string mutex_name = "mutex";
    static inline const std::string condition_name = "condition";
    static inline const std::string users_name = "users";
    static inline const std::string messages_name = "messages";
    static inline const std::string vector_size_name = "vector_size";

private:

    std::string m_user_name;
    std::atomic < bool > m_exit_flag;

    std::string shared_memory_name;
    shared_memory_t m_shared_memory;
    deque_t* m_deque;
    mutex_t* m_mutex;
    condition_t* m_condition;
    counter_t* m_users;
    counter_t* count_delete_messeages;
    std::size_t m_local_messages = 0;
    counter_t* vector_size;
};

int main(int argc, char** argv)
{
    std::string user_name;

    std::string chat_name;

    std::cout << "Enter your name: ";

    std::getline(std::cin, user_name);

    std::cout << "Enter chat name: ";

    std::getline(std::cin, chat_name);


    Chat(user_name, chat_name).run();

    system("pause");

    return EXIT_SUCCESS;
}