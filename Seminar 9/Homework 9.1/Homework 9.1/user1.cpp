#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <mutex>
#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/containers/string.hpp>


int main(int argc, char** argv)
{
	system("pause");

	using allocator = boost::interprocess::allocator < std::string,
		boost::interprocess::managed_shared_memory::segment_manager >;

	/*using string = boost::interprocess::basic_string < char,
		std::char_traits < char >, allocator>;*/

	using vector = boost::interprocess::vector < std::string, allocator>;

	const std::string shared_memory_name = "managed_shared_memory";
	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);

	auto text = shared_memory.find_or_construct < vector >("Vector")(shared_memory.get_segment_manager());

	const std::string mutex_name = "mutex";
	const std::string condition_name = "condition";

	auto m =
		shared_memory.find_or_construct < boost::interprocess::interprocess_mutex >(mutex_name.c_str())();
	auto c =
		shared_memory.find_or_construct < boost::interprocess::interprocess_condition >(condition_name.c_str())();

	std::cout << "user1 active\n";

	std::string value;
	do {
		//import block

		if (text->size() > 0)
		{
			std::unique_lock lock(*m);

			c->wait(lock, [text]() {return !text->empty(); });

			value = text->back();

			text->pop_back();

			std::cout << value << std::endl;

			continue;
		}

		//export block

		if (std::cin >> value)
		{

			boost::interprocess::scoped_lock lock(*m);

			if (value == "exit")
				text->push_back("user disconect");
			else
				text->push_back(value);

			c->notify_one();
		}

	} while (value != "exit");

	system("pause");

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
}