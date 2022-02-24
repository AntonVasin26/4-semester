#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "Timer.hpp"
#include <algorithm>
#include <iterator>
#include <random>
#include <boost/functional/hash.hpp>
#include <fstream>

std::set < std::string > make_random_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
	std::uniform_int_distribution <> letter(97, 122);
	std::default_random_engine e(static_cast <std::size_t> (
		std::chrono::system_clock::now().time_since_epoch().count()));

	std::set < std::string > words;

	for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
		for (auto& c : s)
			c = letter(e);

	return words;
}

int main()
{
	//Double
	std::set<double> init_s;
	int s_lengh = 2000000;
	std::uniform_real_distribution<double> unif(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
	std::default_random_engine re;
	while (std::size(init_s) < s_lengh)
	{
		init_s.insert(unif(re));
	}

	std::set<std::size_t> s1;
	boost::hash<double> double_hash;
	int c = 0;
	std::vector<int> y;
	for (auto element : init_s)
	{
		s1.insert(double_hash(element));
		c++;
		if (c%10000==0)
		{
			y.push_back(c-std::size(s1));
		}
	}

	std::ofstream fout;
	fout.open("for_ex2.txt");
	fout << "Double\n";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}
	//


	
	//Int
	fout << "\n\n\n Int\n";
	std::set<int> init_s1;
	std::uniform_real_distribution<double> unif1(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	std::default_random_engine re1;
	while (std::size(init_s1) < s_lengh)
	{
		init_s1.insert(unif1(re1));
	}

	s1.clear();
	boost::hash<int> int_hash;
	c = 0;
	y.clear();
	for (auto element : init_s1)
	{
		s1.insert(int_hash(element));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}
	//



	//string
	fout << "\n\n\n string\n";
	auto init_s2 = make_random_words(s_lengh, 10);

	s1.clear();
	boost::hash<std::string> string_hash;
	c = 0;
	y.clear();
	for (auto element : init_s2)
	{
		s1.insert(string_hash(element));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}
	//
}