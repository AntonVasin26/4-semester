#include <fstream>
#include "Hash_functions.hpp"


int main()
{
	int s_lengh = 2000000;
	auto init_s = make_random_words(s_lengh, 10);

	std::set<std::size_t> s1;
	std::vector<int> y;
	int c = 0;
	for (auto element : init_s)
	{
		s1.insert(RSHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	std::ofstream fout;
	fout.open("for_ex3.txt");
	fout << "RSHash";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}


	c = 0;
	s1.clear();
	y.clear();
	for (auto element : init_s)
	{
		s1.insert(JSHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	fout << "\n\nJSHash";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}



	c = 0;
	s1.clear();
	y.clear();
	for (auto element : init_s)
	{
		s1.insert(PJWHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	fout << "\n\nPJWHash";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}



	c = 0;
	s1.clear();
	y.clear();
	for (auto element : init_s)
	{
		s1.insert(ELFHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	fout << "\n\nELFHash";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}
}