#include "Header.hpp"

void show_currency_symbol(const std::string& locale_name)
{
	std::cout << locale_name << " : " <<
		std::use_facet < std::moneypunct < char, false > >(
			std::locale(locale_name)).curr_symbol() << std::endl;
}

void print(std::u8string s1)
{
	std::copy(std::cbegin(s1), std::cend(s1),
		std::ostream_iterator < char >(std::cout, " "));
	std::cout << '\n';
}

int main()
{
	SetConsoleCP(CP_UTF8); // настраиваем консоль, чтобы она могла корректно
	SetConsoleOutputCP(CP_UTF8); // работать с выводом символов в кодировке UTF-8
	std::u8string s1;
	std::u8string s2;
	std::copy(std::istream_iterator < char >(std::cin), std::istream_iterator < char >(), std::back_inserter(s2));
	std::cout << '\n';
	print(s2);

	s1 = boost::locale::conv::utf_to_utf < char8_t, char >(s2);
	//std::cout << '\n' << s1 << '\n';
	
	//double value;
	//std::cin >> value;
	//std::cout.imbue(std::locale("ru_RU.utf8"));
	//std::cout << std::showbase << std::put_money(value, false) << std::endl;

}