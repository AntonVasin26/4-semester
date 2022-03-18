#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>

#include <boost/locale.hpp>

#include <Windows.h>


std::string translit(const std::u32string& word)
{
	std::unordered_map <char32_t, std::string> tr = {
	{U'А',"A"},
	{U'Б',"B"},
	{U'В',"V"},
	{U'Г',"G"},
	{U'Д',"D"},
	{U'Е',"E"},
	{U'Ё',"JO"},
	{U'Ж',"ZH"},
	{U'З',"Z"},
	{U'И',"I"},
	{U'Й',"J"},
	{U'К',"K"},
	{U'Л',"L"},
	{U'М',"M"},
	{U'Н',"N"},
	{U'О',"O"},
	{U'П',"P"},
	{U'Р',"R"},
	{U'С',"S"},
	{U'Т',"T"},
	{U'У',"U"},
	{U'Ф',"F"},
	{U'Х',"KH"},
	{U'Ц',"C"},
	{U'Ч',"CH"},
	{U'Ш',"SH"},
	{U'Щ',"SHH"},
	{U'Ъ',"\""},
	{U'Ы',"Y"},
	{U'Ь',"\'"},
	{U'Э',"EH"},
	{U'Ю',"JU"},
	{U'Я',"JA"},
	{U'а',"a"},
	{U'б',"b"},
	{U'в',"v"},
	{U'г',"g"},
	{U'д',"d"},
	{U'е',"e"},
	{U'ё',"jo"},
	{U'ж',"zh"},
	{U'з',"z"},
	{U'и',"i"},
	{U'й',"j"},
	{U'к',"k"},
	{U'л',"l"},
	{U'м',"m"},
	{U'н',"n"},
	{U'о',"o"},
	{U'п',"p"},
	{U'р',"r"},
	{U'с',"s"},
	{U'т',"t"},
	{U'у',"u"},
	{U'ф',"f"},
	{U'х',"kh"},
	{U'ц',"c"},
	{U'ч',"ch"},
	{U'ш',"sh"},
	{U'щ',"shh"},
	{U'ъ',"\""},
	{U'ы',"y"},
	{U'ь',"\'"},
	{U'э',"eh"},
	{U'ю',"ju"},
	{U'я',"ja"}};
std::string result;
for (auto letter : word)
{
	if (U'А' <= letter && letter <= U'я') {
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
std::cout << "ex2\n\nВведите предложение на русском:\n";
std::getline(std::cin, s1);//"Шла Саша по шоссе и сосала сушку"
boost::locale::generator generator;
generator.locale_cache_enabled(true);
std::locale locale = generator(boost::locale::util::get_system_locale());
s1 = boost::locale::conv::to_utf < char >(s1, locale);
std::u32string su32 = boost::locale::conv::utf_to_utf <char32_t, char>(s1);
auto answer = translit(su32);
std::cout << "Предложение в транслите:\n";
std::cout << answer;
}