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


int main(int argc, char** argv)
{
	system("pause");

	const std::string shared_memory_name = "managed_shared_memory";

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_only, shared_memory_name.c_str());

	using allocator = boost::interprocess::allocator < int,
		boost::interprocess::managed_shared_memory::segment_manager >;

	using vector = boost::interprocess::vector < int, allocator>;

	auto v = shared_memory.find <vector>("Vector").first;

	const std::string mutex_name = "mutex";
	const std::string condition_name = "condition";

	boost::interprocess::interprocess_mutex* m =
		shared_memory.find_or_construct < boost::interprocess::interprocess_mutex >(mutex_name.c_str())();
	auto c =
		shared_memory.find < boost::interprocess::interprocess_condition >(condition_name.c_str()).first;

	int value = 0;
	while (true)
	{
		std::unique_lock lock(*m);

		c->wait(lock, [v]() {return !v->empty(); });

		value = v->back();

		v->pop_back();

		std::cout << value << std::endl;

		if (value == 0)
		{
			break;
		}
	}

	system("pause");

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
}