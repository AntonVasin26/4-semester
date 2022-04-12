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

	using allocator = boost::interprocess::allocator < int,
		boost::interprocess::managed_shared_memory::segment_manager >;

	using vector = boost::interprocess::vector < int, allocator>;

//import block

	const std::string shared_memory_name_im = "managed_shared_memory";

	boost::interprocess::managed_shared_memory shared_memory_im(
		boost::interprocess::open_only, shared_memory_name_im.c_str());

	auto import_text = shared_memory_im.find <vector>("Vector").first;

//export block

	const std::string shared_memory_name_ex = "managed_shared_memory";

	boost::interprocess::shared_memory_object::remove(shared_memory_name_ex.c_str());

	boost::interprocess::managed_shared_memory shared_memory_ex(
		boost::interprocess::create_only, shared_memory_name_ex.c_str(), 1024);

	auto export_text = shared_memory.construct < vector >("Vector")(shared_memory.get_segment_manager());

	const std::string mutex_name = "mutex";
	const std::string condition_name = "condition";

	auto m =
		shared_memory.find < boost::interprocess::interprocess_mutex >(mutex_name.c_str()).first;
	auto c =
		shared_memory.find < boost::interprocess::interprocess_condition >(condition_name.c_str()).first;

	std::cout << "user2 active\n";

	std::string value = 0;
	do {
		//import block

		if (import_text->size() > 0)
		{
			std::unique_lock lock(*m);

			c->wait(lock, [import_text]() {return !import_text->empty(); });

			value = import_text->back();

			import_text->pop_back();

			std::cout << value << std::endl;

			continue;
		}

		//export block
		
		std::cout << "export block\n";

		if (std::cin >> value)
		{

			boost::interprocess::scoped_lock lock(*m);

			if (value == "exit")
				export_text->push_back("user disconect");
			else
				export_text->push_back(value);

			c->notify_one();
		}

	} while (value != "exit");

	system("pause");

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
}