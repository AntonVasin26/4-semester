#include <string>
#include <iostream>

int main()
{
	char ch{ 109 };
	std::string input;
	std::cin >> input;
	if (input[1] == ch)
		std::cout << "\nok";
}