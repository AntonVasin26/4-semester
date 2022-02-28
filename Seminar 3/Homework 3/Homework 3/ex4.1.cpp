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
		/*0*/	boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Phone_book_parametr, std::string, &Phone_book_parametr::name > >,
		/*1*/	boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Phone_book_parametr, std::string, &Phone_book_parametr::number	> >,
		/*2*/	boost::multi_index::random_access <>,
		/*3*/		boost::multi_index::ordered_non_unique <
		boost::multi_index::member < Phone_book_parametr, std::string, &Phone_book_parametr::name> > > >;

	const enum{find_number,find_name,random, vec};

public:
	void insert(std::string name, std::string number)
	{
		book.insert({ name, number });
	}

	void print_number(std::string name)
	{
		const auto& hashed_name_index = book.get <find_number>();
		auto count = hashed_name_index.count(name);
		auto iterator = hashed_name_index.find(name);
		std::cout << iterator->name << ": " << count << '\n';
		for (auto i = 0; i < count; ++i)
			std::cout << (iterator++)->number << '\n';
		return;
	}
	auto get_number(std::string name)
	{
		const auto& hashed_name_index = book.get <find_number>();
		return std::make_pair(hashed_name_index.find(name), hashed_name_index.count(name));
	}


	void print_name(std::string number)
	{
		const auto& hashed_number_index = book.get <find_name>();
		auto count1 = hashed_number_index.count(number);
		auto iterator1 = hashed_number_index.find(number);
		std::cout << iterator1->number << ": " << count1 << '\n';
		for (auto i = 0; i < count1; ++i)
				std::cout << (iterator1++)->name << '\n';
	}
	auto get_name(std::string number)
	{
		const auto& hashed_number_index = book.get <find_name>();
		return std::make_pair(hashed_number_index.find(number), hashed_number_index.count(number));
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

	
	auto p = book.get_name("3456767");
	for (auto i = 0; i < p.second; ++i)
		std::cout << (p.first++)->name << '\n';

	std::cout << '\n';

	/*const auto& hashed_number_index = book.get <1>();
	auto count1 = hashed_number_index.count("9233487");
	auto iterator1 = hashed_number_index.find("9233487");
	std::cout << iterator1->number << ": " << count1 << '\n';
	for (auto i = 0; i < count1; ++i)
		std::cout << (iterator1++)->name << '\n';

	std::cout << '\n' << "Random Name\n";
	const auto& random_access_index = book.get < 2 >();
	std::cout << random_access_index[2].name << ": " << random_access_index[2].number << '\n';

	std::cout << '\n' << "Name with A" << '\n';
	const auto& ordered_name_index = book.get < 3 >();
	auto begin = ordered_name_index.lower_bound("A");
	const auto end = ordered_name_index.upper_bound("B");
	for (; begin != end; ++begin)
		std::cout << begin->name << ": " << begin->number << '\n';

*/

}

