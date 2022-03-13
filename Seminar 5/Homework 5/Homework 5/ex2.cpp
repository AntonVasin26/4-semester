#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#ifndef _HAS_AUTO_PTR_ETC
#define _HAS_AUTO_PTR_ETC 1
#endif

#include <bitset>
#include <chrono>
#include <codecvt>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include <boost/locale.hpp>

#include <Windows.h>


std::wstring convert_utf8_to_wstring(const std::string& string)
{
std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter;
return converter.from_bytes(string);
}

std::string convert_wstring_to_utf8(const std::wstring& wstring)
{
std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter;
return converter.to_bytes(wstring);
}

std::wstring convert_string_to_wstring(
const std::string& string,
const std::locale& locale = std::locale())
{
std::vector < wchar_t > buffer(string.size());

std::use_facet < std::ctype < wchar_t > >(locale).widen(
string.data(),
string.data() + string.size(),
buffer.data());

return std::wstring(buffer.data(), buffer.size());
}

std::string convert_wstring_to_string(
const std::wstring& wstring,
const std::locale& locale = std::locale())
{
std::vector < char > buffer(wstring.size());

std::use_facet < std::ctype < wchar_t > >(locale).narrow(
wstring.data(),
wstring.data() + wstring.size(),
'?', buffer.data()); // default character

return std::string(buffer.data(), buffer.size());
}

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
	{U'�',{34}},
	{U'�',U"y"},
	{U'�',U"\'"},
	{U'�',U"eh"},
	{U'�',U"ju"},
	{U'�',U"ja"}};
std::u32string result;
for (auto letter : word)
{
	//if (U'�' <= letter && letter <= U'�')
	//{
	result += tr[letter];
	//}
	//else
	//{
	//result += letter;
	//}
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
auto ws1 = convert_string_to_wstring(s1);
s1 = convert_wstring_to_utf8(ws1);
std::u32string su32 = boost::locale::conv::utf_to_utf <char32_t, char>(s1);
auto answer = translit(su32);
s1 = boost::locale::conv::utf_to_utf <char, char32_t>(answer);
ws1 = convert_utf8_to_wstring(s1);
s1 = convert_wstring_to_string(ws1);
std::cout << '\n' << s1;
}