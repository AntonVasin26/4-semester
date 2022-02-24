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
	fout << "1)RSHash\n";
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

	fout << "\n\n2)JSHash\n";
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

	fout << "\n\n3)PJWHash\n";
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

	fout << "\n\n4)ELFHash\n";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}

	c = 0;
	s1.clear();
	y.clear();
	for (auto element : init_s)
	{
		s1.insert(BKDRHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	fout << "\n\n5)BKDRHash\n";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}

	c = 0;
	s1.clear();
	y.clear();
	for (auto element : init_s)
	{
		s1.insert(SDBMHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	fout << "\n\n6)SDBMHash\n";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}

	c = 0;
	s1.clear();
	y.clear();
	for (auto element : init_s)
	{
		s1.insert(DJBHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	fout << "\n\n7)DJBHash\n";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}

	c = 0;
	s1.clear();
	y.clear();
	for (auto element : init_s)
	{
		s1.insert(DEKHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	fout << "\n\n8)DEKHash\n";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}

	c = 0;
	s1.clear();
	y.clear();
	for (auto element : init_s)
	{
		s1.insert(APHash(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}

	fout << "\n\n9)APHash\n";
	for (auto i = 0; i < std::size(y); ++i)
	{
		fout << y[i] << '\n';
	}
}