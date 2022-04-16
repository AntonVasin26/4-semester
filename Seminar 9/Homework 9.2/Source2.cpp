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
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

class Chat
{
private:

    using shared_memory_t = boost::interprocess::managed_shared_memory;
    using manager_t = shared_memory_t::segment_manager;
    using string_allocator_t = boost::interprocess::allocator <char, manager_t>;
    using string_t = boost::interprocess::basic_string <char, std::char_traits <char>, string_allocator_t>;
    using vector_allocator_t = boost::interprocess::allocator <string_t, manager_t>;
    using vector_t = boost::interprocess::vector <string_t, vector_allocator_t>;
    using mutex_t = boost::interprocess::interprocess_mutex;
    using condition_t = boost::interprocess::interprocess_condition;
    using counter_t = std::atomic < std::size_t >;

public:

    explicit Chat(const std::string& user_name, const std::string& chat_name) : m_user_name(user_name), m_exit_flag(false), shared_memory_name(chat_name)
    {
        m_shared_memory = shared_memory_t(boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);

        m_vector = m_shared_memory.find_or_construct < vector_t >(vector_name.c_str())(m_shared_memory.get_segment_manager());
        m_mutex = m_shared_memory.find_or_construct < mutex_t >(mutex_name.c_str())();
        m_condition = m_shared_memory.find_or_construct < condition_t >(condition_name.c_str())();
        m_users = m_shared_memory.find_or_construct < counter_t >(users_name.c_str())(0);
        m_messages = m_shared_memory.find_or_construct < counter_t >(messages_name.c_str())();

        (*m_users)++;
    }

    ~Chat() noexcept = default;

public:

    void run()
    {
        auto reader = std::thread(&Chat::read, this);

        write();

        reader.join();

        send_message(m_user_name + " left the chat");

        if (!(--(*m_users)))
        {
            m_users--;
        }
        else
        {
            boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
        }
    }

private:

    void read()
    {
        send_message(m_user_name + " joined the chat");

        while (true)
        {
            std::unique_lock lock(*m_mutex);
            m_condition->wait(lock, [this]() { return !m_vector->empty(); });

            //if ((*m_vector).back() == "vector cleared")
            //{
            //    m_local_messages -= 1;
            //}

            if (m_exit_flag)
            {
                break;
            }

            while (m_vector->size() != m_local_messages)
            {
                std::cout << (*m_vector)[m_local_messages] << std::endl;
                m_local_messages++;
            }
        }
    }

    void show_history()
    {
        std::scoped_lock lock(*m_mutex);

        for (const auto& message : *m_vector)
        {
            std::cout << message << std::endl;
        }
    }

    void send_message(const std::string& message)
    {
        boost::interprocess::scoped_lock lock(*m_mutex);

        m_vector->push_back(string_t((m_user_name + ": " + message).c_str(),
            m_shared_memory.get_segment_manager()));

        //if (m_vector->size() > 3)
        //{
        //    m_vector->push_back(string_t(size_vec_flag.c_str(), m_shared_memory.get_segment_manager()));
        //    m_vector->erase(m_vector->begin(), m_vector->begin()+2);
        //    m_local_messages -= 1;
        //}

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

            send_message(message);

        }
    }

private:
    static inline const std::string size_vec_flag = "vector cleared";
    static inline const std::string vector_name = "vector";
    static inline const std::string mutex_name = "mutex";
    static inline const std::string condition_name = "condition";
    static inline const std::string users_name = "users";
    static inline const std::string messages_name = "messages";

private:

    std::string m_user_name;
    std::string shared_memory_name;
    std::atomic < bool > m_exit_flag;

    shared_memory_t m_shared_memory;
    vector_t* m_vector;
    mutex_t* m_mutex;
    condition_t* m_condition;
    counter_t* m_users;
    counter_t* m_messages;
    std::size_t m_local_messages = 0;
};

int main(int argc, char** argv)
{
    std::string user_name;

    std::string chat_name = "shared_memory";

    std::cout << "Enter your name: ";

    std::getline(std::cin, user_name);

    Chat(user_name, chat_name).run();

    system("pause");

    return EXIT_SUCCESS;
}