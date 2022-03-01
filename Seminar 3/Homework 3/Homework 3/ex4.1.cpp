#include <iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <vector>


class Phone_book
{
	struct Phone_book_parametr
	{
		std::string name;
		std::string number;
	};
	using Phone_book_multi_index = boost::multi_index::multi_index_container <
		Phone_book_parametr, boost::multi_index::indexed_by <
		/*0*/	boost::multi_index::hashed_unique <
		boost::multi_index::member < Phone_book_parametr, std::string, &Phone_book_parametr::name > >,
		/*1*/	boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Phone_book_parametr, std::string, &Phone_book_parametr::number	> >,
		/*2*/	boost::multi_index::random_access <>,
		/*3*/		boost::multi_index::ordered_non_unique <
		boost::multi_index::member < Phone_book_parametr, std::string, &Phone_book_parametr::name> > > >;

	const enum{find_number,find_name,random_access, vec};

public:
	void insert(std::string name = "Ivanov Ivan Ivanovich", std::string number = "1234567")
	{
		const auto& hashed_name_index = book.get <find_number>();
		const auto count = hashed_name_index.count(name);
		if (count)
		{
			const auto iterator = hashed_name_index.find(name);
			std::cout << "such a name already exists: " << iterator->name << " - " << iterator->number << '\n';
		}
		book.insert({ name, number });
	}

	void print_number(std::string name = "Ivanov Ivan Ivanovich")
	{
		const auto& hashed_name_index = book.get <find_number>();
		const auto count = hashed_name_index.count(name);
		if (count)
		{
			const auto iterator = hashed_name_index.find(name);
			std::cout << iterator->name << " - " << (iterator)->number << '\n';
		}
		else
			std::cout << "not found\n";
	}

	void print_name(std::string number = "1234567")
	{
		const auto& hashed_number_index = book.get <find_name>();
		const auto count = hashed_number_index.count(number);
		if (count)
		{
			auto iterator = hashed_number_index.find(number);
			std::cout << (iterator)->number << " - " << count << '\n';
			for (auto i = 0; i < count; ++i)
				std::cout << (iterator++)->name << '\n';
		}
		else
			std::cout << "not found\n";
	}

	void del_name(std::string name = "Ivanov Ivan Ivanovich")
	{
		auto& hashed_name_index = book.get <find_number>();
		const auto count = hashed_name_index.count(name);
		if (count)
		{
			const auto iterator = hashed_name_index.find(name);
			std::cout << iterator->name << " - " << (iterator)->number << " (deletion is successful)\n";
			book.erase(iterator);
		}
		else
			std::cout << "not found\n";
	}

	void update_number(std::string name = "Ivanov Ivan Ivanovich" , std::string number = "1234567")
	{
		auto& hashed_name_index = book.get <find_number>();
		const auto count = hashed_name_index.count(name);
		if (count)
		{
			const auto iterator = hashed_name_index.find(name);
			hashed_name_index.modify(iterator, [number](Phone_book_parametr& element) {element.number = number; });
			std::cout << name << " - " << (iterator)->number << " (replacement is successful)\n";
		}
		else
			std::cout << "not found";
	}

	void get(unsigned int i)
	{

		const auto& random_access_index = book.get < random_access >();
		if (i < std::size(random_access_index))
			std::cout << random_access_index[i].name << " - " << random_access_index[i].number << '\n';
		else
			std::cout << "out of range; size = " << std::size(random_access_index) << '\n';
	}

	void sorted_plot(std::string upper_bound = "A", std::string lower_bound = "Z")
	{
		const auto& ordered_name_index = book.get < vec >();
		auto begin = ordered_name_index.lower_bound(upper_bound);
		const auto end = ordered_name_index.upper_bound(lower_bound);
		for (; begin != end; ++begin)
			std::cout << begin->name << " - " << begin->number << '\n';
	}

	size_t size()
	{
		const auto& random_access_index = book.get < random_access >();
		return  std::size(random_access_index);
	}

private:
	Phone_book_multi_index book;
};




int main()
{
	Phone_book book;

	book.insert( "Ana", "2547654" );
	book.insert( "Vova", "4562345" );
	book.insert( "Pavel", "6433476" );
	book.insert( "Vera", "9233487" );
	book.insert( "Ana", "3456767" );
	book.insert( "Alex", "9233487" );
	book.insert( "Alex", "3456767" );
	book.insert("Al", "4454432");
	book.insert("Ivan", "9233487");
	std::cout << '\n';

	
	book.print_name("9233487");
	std::cout << '\n';
	book.print_name("Niko");
	std::cout << '\n';
	book.print_number("Ana");
	std::cout << '\n';
	book.del_name("Alex");
	std::cout << '\n';
	book.update_number("Ana", "2223344");
	std::cout << '\n';
	book.print_number("Ana");
	std::cout << '\n';
	std::cout << book.size() << '\n';
	std::cout << '\n';
	book.get(15);
	std::cout << '\n';
	book.get(4);
	std::cout << '\n';
	book.sorted_plot();
}

