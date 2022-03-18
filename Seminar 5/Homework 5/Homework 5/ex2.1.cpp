#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>

#include <boost/locale.hpp>

#include <Windows.h>


std::u32string translit(const std::u32string& word)
{
	std::unordered_map <char32_t, std::u32string> tr = {
	{U'À',U"A"},
	{U'Á',U"B"},
	{U'Â',U"V"},
	{U'Ã',U"G"},
	{U'Ä',U"D"},
	{U'Å',U"E"},
	{U'¨',U"JO"},
	{U'Æ',U"ZH"},
	{U'Ç',U"Z"},
	{U'È',U"I"},
	{U'É',U"J"},
	{U'Ê',U"K"},
	{U'Ë',U"L"},
	{U'Ì',U"M"},
	{U'Í',U"N"},
	{U'Î',U"O"},
	{U'Ï',U"P"},
	{U'Ð',U"R"},
	{U'Ñ',U"S"},
	{U'Ò',U"T"},
	{U'Ó',U"U"},
	{U'Ô',U"F"},
	{U'Õ',U"KH"},
	{U'Ö',U"C"},
	{U'×',U"CH"},
	{U'Ø',U"SH"},
	{U'Ù',U"SHH"},
	{U'Ú',{34} },
	{U'Û',U"Y"},
	{U'Ü',U"\'"},
	{U'Ý',U"EH"},
	{U'Þ',U"JU"},
	{U'ß',U"JA"},
	{U'à',U"a"},
	{U'á',U"b"},
	{U'â',U"v"},
	{U'ã',U"g"},
	{U'ä',U"d"},
	{U'å',U"e"},
	{U'¸',U"jo"},
	{U'æ',U"zh"},
	{U'ç',U"z"},
	{U'è',U"i"},
	{U'é',U"j"},
	{U'ê',U"k"},
	{U'ë',U"l"},
	{U'ì',U"m"},
	{U'í',U"n"},
	{U'î',U"o"},
	{U'ï',U"p"},
	{U'ð',U"r"},
	{U'ñ',U"s"},
	{U'ò',U"t"},
	{U'ó',U"u"},
	{U'ô',U"f"},
	{U'õ',U"kh"},
	{U'ö',U"c"},
	{U'÷',U"ch"},
	{U'ø',U"sh"},
	{U'ù',U"shh"},
	{U'ú',U"\""},
	{U'û',U"y"},
	{U'ü',U"\'"},
	{U'ý',U"eh"},
	{U'þ',U"ju"},
	{U'ÿ',U"ja"} };
	std::u32string result;
	for (auto letter : word)
	{
		if (U'À' <= letter && letter <= U'ÿ') {
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
	s1 = "ÀÍÒÎÍ";
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