#include <iostream>
#include <fstream>
#include <string>



int main()
{
	long int n_str;
	const long int l = 23; //Number of characters
	std::fstream fin("for_ex2.txt", std::ios::in);
	std::cout << "Enter the line number 0-9: ";
	std::cin >> n_str;
	fin.seekg((l+2)*n_str); //Why plus 2? Where does the second character come from?
							//The first one is "Enter", and what other symbol?

	std::string line;
	std::getline(fin, line);
	std::cout << line;
	//char ch[24];
	//fin.get(ch, l+1);
	//std::cout << ch;
}