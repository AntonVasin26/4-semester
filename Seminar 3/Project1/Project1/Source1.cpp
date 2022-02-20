#include <iostream>
#include <map>
#include <string>


int main(int argc, char** argv)
{
	std::map <std::string, int > m;
	m["abc"] = 42;
	m.insert(std::make_pair("xyz", 42));

	for (auto [key, value] : m)
	{
		std::cout << key << ' ' << value << std::endl;
	}

	try
	{
		std::cout << m["a"] << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}