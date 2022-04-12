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
	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::create_only, shared_memory_name.c_str(), 1024);

	using allocator = boost::interprocess::allocator < int,
		boost::interprocess::managed_shared_memory::segment_manager >;

	using vector = boost::interprocess::vector < int, allocator>;

	auto v = shared_memory.construct < vector >("Vector")(shared_memory.get_segment_manager());

	const std::string mutex_name = "mutex";
	const std::string condition_name = "condition";

	auto m =
		shared_memory.construct < boost::interprocess::interprocess_mutex >(mutex_name.c_str())();
	auto c =
		shared_memory.construct < boost::interprocess::interprocess_condition >(condition_name.c_str())();

	int value = 0;
	while (std::cin >> value)
	{
		boost::interprocess::scoped_lock lock(*m);

		v->push_back(value);

		c->notify_one();
	}

	system("pause");

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
}