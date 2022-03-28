#include <iostream>
#include <fstream>
#include <string>



int main()
{
	long int n_str = 4;
	const long int l = 23;
	char ch[23];
	//std::string line;
	std::fstream fin("for_ex2.txt", std::ios::in);
	//std::cin >> n_str;
	fin.seekg((l+2)*n_str);
	fin.get(ch, l);
	//std::getline(fin, line);
	std::cout << ch;
	//std::cout << line;
	
}