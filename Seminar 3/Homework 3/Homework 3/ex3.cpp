#include <fstream>
#include "Hash_functions.hpp"
#include <functional>

template <typename Func>
void n_of_collisions(Func&& f, std::set<std::size_t>& s1, std::set<std::string>&  init_s, std::vector<int>& y)
{
	int c = 0;
	for (auto element : init_s)
	{
		s1.insert(f(element.c_str(), 10));
		c++;
		if (c % 10000 == 0)
		{
			y.push_back(c - std::size(s1));
		}
	}
}

void add_in_file(std::ofstream& fout, std::string name_section, std::vector<int>& input_value)
{

	fout << '\n' << name_section << '\n';
	for (auto i = 0; i < std::size(input_value); ++i)
	{
		fout << input_value[i] << '\n';
	}
}
int main()
{
	const int s_lengh = 2000000;
	auto init_s = make_random_words(s_lengh, 10);

	std::set<std::size_t> s1;
	std::vector<int> y;

	std::vector< std::pair<std::string, std::function<int(const char*,unsigned int)> > > v;
	v.push_back(std::make_pair("1)RShash\n", RSHash));
	v.push_back(std::make_pair("2)JSHash", JSHash));
	v.push_back(std::make_pair("3)PKWHash", PJWHash));
	v.push_back(std::make_pair("4)ELFHash", ELFHash));
	v.push_back(std::make_pair("5)BKDRHash", BKDRHash));
	v.push_back(std::make_pair("6)SDBMHash", SDBMHash));
	v.push_back(std::make_pair("7)DJBHash", DJBHash));
	v.push_back(std::make_pair("8)DEKHash", DEKHash));
	v.push_back(std::make_pair("9)APHash", APHash));

	std::ofstream fout;
	fout.open("for_ex3.txt");
	for (auto func : v)
	{
		s1.clear();
		y.clear();
		n_of_collisions(func.second, s1, init_s, y);
		add_in_file(fout, func.first, y);
	}
	fout.close();
}