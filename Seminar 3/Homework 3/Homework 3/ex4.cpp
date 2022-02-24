#include <iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <vector>

struct Phone_book
{
	std::string name;
	std::string number;
};

int main()
{

	using Phone_book_multi_index = boost::multi_index::multi_index_container <
		Phone_book, boost::multi_index::indexed_by <
/*0*/	boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Phone_book, std::string, &Phone_book::name > >,
/*1*/	boost::multi_index::hashed_non_unique <
		boost::multi_index::member < Phone_book, std::string, &Phone_book::number	> >,
/*2*/	boost::multi_index::random_access <>,
/*3*/		boost::multi_index::ordered_non_unique <
		boost::multi_index::member < Phone_book, std::string, &Phone_book::name> > > >;

	Phone_book_multi_index book;

	book.insert({ "Ana", "2547654" });
	book.insert({ "Vova", "4562345" });
	book.insert({ "Pavel", "6433476" });
	book.insert({ "Vera", "9233487" });
	book.insert({ "Ana", "3456767" });
	book.insert({ "Alex", "9233487" });
	book.insert({ "Alex", "3456776" });

	const auto& hashed_name_index = book.get <0>();
	auto count = hashed_name_index.count("Ana");
	auto iterator = hashed_name_index.find("Ana");
	std::cout << iterator->name << ": " << count << '\n';
	for (auto i = 0; i < count; ++i)
		std::cout << (iterator++)->number << '\n';


	std::cout << '\n';

	const auto& hashed_number_index = book.get <1>();
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



}

