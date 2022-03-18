#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>

#include <boost/locale.hpp>

#include <Windows.h>


std::u32string translit(const std::u32string& word)
{
	std::unordered_map <char32_t, std::u32string> tr = {
	{U'�',U"A"},
	{U'�',U"B"},
	{U'�',U"V"},
	{U'�',U"G"},
	{U'�',U"D"},
	{U'�',U"E"},
	{U'�',U"JO"},
	{U'�',U"ZH"},
	{U'�',U"Z"},
	{U'�',U"I"},
	{U'�',U"J"},
	{U'�',U"K"},
	{U'�',U"L"},
	{U'�',U"M"},
	{U'�',U"N"},
	{U'�',U"O"},
	{U'�',U"P"},
	{U'�',U"R"},
	{U'�',U"S"},
	{U'�',U"T"},
	{U'�',U"U"},
	{U'�',U"F"},
	{U'�',U"KH"},
	{U'�',U"C"},
	{U'�',U"CH"},
	{U'�',U"SH"},
	{U'�',U"SHH"},
	{U'�',{34} },
	{U'�',U"Y"},
	{U'�',U"\'"},
	{U'�',U"EH"},
	{U'�',U"JU"},
	{U'�',U"JA"},
	{U'�',U"a"},
	{U'�',U"b"},
	{U'�',U"v"},
	{U'�',U"g"},
	{U'�',U"d"},
	{U'�',U"e"},
	{U'�',U"jo"},
	{U'�',U"zh"},
	{U'�',U"z"},
	{U'�',U"i"},
	{U'�',U"j"},
	{U'�',U"k"},
	{U'�',U"l"},
	{U'�',U"m"},
	{U'�',U"n"},
	{U'�',U"o"},
	{U'�',U"p"},
	{U'�',U"r"},
	{U'�',U"s"},
	{U'�',U"t"},
	{U'�',U"u"},
	{U'�',U"f"},
	{U'�',U"kh"},
	{U'�',U"c"},
	{U'�',U"ch"},
	{U'�',U"sh"},
	{U'�',U"shh"},
	{U'�',U"\""},
	{U'�',U"y"},
	{U'�',U"\'"},
	{U'�',U"eh"},
	{U'�',U"ju"},
	{U'�',U"ja"} };
	std::u32string result;
	for (auto letter : word)
	{
		if (U'�' <= letter && letter <= U'�') {
			result += tr[letter];
		}
		else
		{
			result += letter;
		}
	}
	return result;
}

int main()
{
	system("chcp 1251");
	std::string s1;
	//std::cin >> s1;
	s1 = "�����";
	std::cout << s1;
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);
	std::locale locale = generator(boost::locale::util::get_system_locale());
	s1 = boost::locale::conv::to_utf < char >(s1, locale);
	std::u32string su32 = boost::locale::conv::utf_to_utf <char32_t, char>(s1);
	auto answer = translit(su32);
	s1 = boost::locale::conv::utf_to_utf <char, char32_t>(answer);
	s1 = boost::locale::conv::from_utf < char >(s1, locale);
	std::cout << '\n' << s1;
}