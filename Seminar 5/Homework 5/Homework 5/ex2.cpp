#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>

#include <boost/locale.hpp>

#include <Windows.h>


std::string translit(const std::u32string& word)
{
	std::unordered_map <char32_t, std::string> tr = {
	{U'�',"A"},
	{U'�',"B"},
	{U'�',"V"},
	{U'�',"G"},
	{U'�',"D"},
	{U'�',"E"},
	{U'�',"JO"},
	{U'�',"ZH"},
	{U'�',"Z"},
	{U'�',"I"},
	{U'�',"J"},
	{U'�',"K"},
	{U'�',"L"},
	{U'�',"M"},
	{U'�',"N"},
	{U'�',"O"},
	{U'�',"P"},
	{U'�',"R"},
	{U'�',"S"},
	{U'�',"T"},
	{U'�',"U"},
	{U'�',"F"},
	{U'�',"KH"},
	{U'�',"C"},
	{U'�',"CH"},
	{U'�',"SH"},
	{U'�',"SHH"},
	{U'�',"\""},
	{U'�',"Y"},
	{U'�',"\'"},
	{U'�',"EH"},
	{U'�',"JU"},
	{U'�',"JA"},
	{U'�',"a"},
	{U'�',"b"},
	{U'�',"v"},
	{U'�',"g"},
	{U'�',"d"},
	{U'�',"e"},
	{U'�',"jo"},
	{U'�',"zh"},
	{U'�',"z"},
	{U'�',"i"},
	{U'�',"j"},
	{U'�',"k"},
	{U'�',"l"},
	{U'�',"m"},
	{U'�',"n"},
	{U'�',"o"},
	{U'�',"p"},
	{U'�',"r"},
	{U'�',"s"},
	{U'�',"t"},
	{U'�',"u"},
	{U'�',"f"},
	{U'�',"kh"},
	{U'�',"c"},
	{U'�',"ch"},
	{U'�',"sh"},
	{U'�',"shh"},
	{U'�',"\""},
	{U'�',"y"},
	{U'�',"\'"},
	{U'�',"eh"},
	{U'�',"ju"},
	{U'�',"ja"}};
std::string result;
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
std::cout << "ex2\n\n������� ����������� �� �������:\n";
std::getline(std::cin, s1);//"��� ���� �� ����� � ������ �����"
boost::locale::generator generator;
generator.locale_cache_enabled(true);
std::locale locale = generator(boost::locale::util::get_system_locale());
s1 = boost::locale::conv::to_utf < char >(s1, locale);
std::u32string su32 = boost::locale::conv::utf_to_utf <char32_t, char>(s1);
auto answer = translit(su32);
std::cout << "����������� � ���������:\n";
std::cout << answer;
}