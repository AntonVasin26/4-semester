#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <mutex>
#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/pair.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/containers/string.hpp>


int main(int argc, char** argv)
{
	system("pause");

	std::string name_user = "user1";

	using segment_manager_t = boost::interprocess::managed_shared_memory::segment_manager;

	using void_alloc = boost::interprocess::allocator < void, segment_manager_t >;

	using char_alloc = boost::interprocess::allocator < char, segment_manager_t >;
	using string = boost::interprocess::basic_string < char, std::char_traits < char >, char_alloc >;

	using string_alloc = boost::interprocess::allocator < string, segment_manager_t >;
	using pair = boost::interprocess::pair <string, string>;

	using pair_alloc = boost::interprocess::allocator < pair, segment_manager_t >;
	using vector = boost::interprocess::vector < pair, pair_alloc>;

	const std::string shared_memory_name = "managed_shared_memory";

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);

	auto text = shared_memory.find_or_construct < vector >("Vector")(shared_memory.get_segment_manager());

	const std::string mutex_name = "mutex";
	const std::string condition_name = "condition";

	auto m =
		shared_memory.find_or_construct < boost::interprocess::interprocess_mutex >(mutex_name.c_str())();
	auto c =
		shared_memory.find_or_construct < boost::interprocess::interprocess_condition >(condition_name.c_str())();

	auto name = shared_memory.find_or_construct < string >("String1")(shared_memory.get_segment_manager());

	auto mess = shared_memory.find_or_construct < string >("String2")(shared_memory.get_segment_manager());

	pair value(*name, *mess);

	std::string meassage;

	std::cout << "user2 active\n";

	do {
		//import block

		std::cout << text->size() << '\n';

		if (text->size() > 0)
		{
			std::unique_lock lock(*m);

			value = text->back();

			c->wait(lock, [value, name_user]() {return value.first == name_user.c_str(); });

			if ((value).first != name_user.c_str())
			{

				text->pop_back();

				std::cout << (value).second << std::endl;

				continue;
			}
		}

		//export block

		if (std::cin >> meassage)
		{

			boost::interprocess::scoped_lock lock(*m);

			(value).first = name_user.c_str();

			if (meassage == "exit")
			{
				(value).second = "\\\\user disconect\n";
			}
			else
			{
				(value).second = meassage.c_str();
			}

			text->push_back(value);

			std::cout << "iter\n";

			c->notify_one();
		}

	} while (meassage != "exit");

	std::cout << (text->back()).first << ": " << (text->back()).second << '\n';
	text->pop_back();
	std::cout << (text->back()).first << ": " << (text->back()).second << '\n';

	system("pause");

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
}