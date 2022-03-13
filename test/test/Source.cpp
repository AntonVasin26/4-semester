#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>
#include <string>
#include <regex>

#include <Windows.h> 

int main()
{
    std::string str1;
    std::getline(std::cin, str1);
    //std::cout << std::fixed << std::setprecision(2);
    std::istringstream s1(str1);
    if (str1.find("USD"))
        s1.imbue(std::locale("en_US.UTF-8"));
    if (str1.find("RUB"))
        s1.imbue(std::locale("ru_RU.utf8"));
    if (str1.find("GBP"))
        s1.imbue(std::locale("en_GB.utf8"));
    if (str1.find("CNY"))
        s1.imbue(std::locale("zh_Hans.utf8"));
    if (str1.find("EUR"))
        s1.imbue(std::locale("fr_FR.utf8"));
    long double val;
    s1 >> std::get_money(val);

    /*str = "USD  1,234.56";
    std::cout << '"' << str << "\" parsed with the facet directly: ";
    std::istringstream s2(str);
    s2.imbue(std::locale("en_US.UTF-8"));
    auto& f = std::use_facet<std::money_get<char>>(s2.getloc());
    std::ios_base::iostate err;
    std::istreambuf_iterator<char> beg(s2), end;
    f.get(beg, end, true, s2, err, val);
    std::cout << val / 100 << '\n';*/

  /*  using namespace std;
        string s = "parapapa";
        int i = 0;

        for (i = s.find("pa", i++); i != string::npos; i = s.find("pa", i + 1))
            cout << i << endl;*/
}