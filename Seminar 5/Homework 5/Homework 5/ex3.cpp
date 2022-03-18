#include <iostream>
#include <regex>
#include <string>


int main()
{
	std::regex pattern(R"((?: |^)(?:[[:alnum:]](?:\.?[\-\w]+)*)@([[:alnum:]]+(?:\.([\-\w]+))*)\.([[:alnum:]]+))");
	//std::regex pattern(R"((?:[[:alnum:]](?:\.?[\-\w]+)*)@([[:alnum:]]+(?:\.([\-\w]+))*)\.([[:alnum:]]+))");
	std::smatch matches;
	std::string line;
	getline(std::cin, line);
	std::sregex_iterator begin(line.cbegin(), line.cend(), pattern);
	std::sregex_iterator end;

	std::for_each(begin, end, [](const std::smatch& m)
		{
			for (std::size_t i = 0; i < m.size(); ++i)
			{
				std::cout << m[i] << " | ";
			}

			std::cout << std::endl;
		});
}
//vasin.anton@gmail.com my main mail, I also have mail 26062002anton19@gmail.com.Maybe
//I'll create a mail anton-a@mail.ptr.ru .And the following addresses are incorrect
//,aaa@mail.com Ah, BB.@Gmail.com, in whom aaaah.@yandex.ru