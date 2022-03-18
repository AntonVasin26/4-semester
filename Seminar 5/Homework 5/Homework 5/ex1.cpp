#include "Header.hpp"
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
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    std::string str1;
    std::cout << "ex1\n\nEnter the amount of money you want to transfer\n";
    std::getline(std::cin, str1);
    //std::cout << std::fixed << std::setprecision(2);
    std::istringstream s1(str1);
    money::m_units m_u;
    if (str1.find("USD") != std::string::npos) {
        s1.imbue(std::locale("en_US.UTF-8"));
        std::cout.imbue(std::locale("en_US.UTF-8"));
        m_u = money::m_units::USD;
    }
    if (str1.find("RUB") != std::string::npos) {
        s1.imbue(std::locale("ru_RU.utf8"));
        std::cout.imbue(std::locale("ru_RU.utf8"));
        m_u = money::m_units::RUB;
    }
    if (str1.find("GBP") != std::string::npos) {
        s1.imbue(std::locale("en_GB.utf8"));
        std::cout.imbue(std::locale("en_GB.utf8"));
        m_u = money::m_units::GBP;
    }
    if (str1.find("CNY") != std::string::npos) {
        s1.imbue(std::locale("zh_Hans.utf8"));
        std::cout.imbue(std::locale("zh_Hans.utf8"));
        m_u = money::m_units::CNY;
    }
    if (str1.find("EUR") != std::string::npos) {
        s1.imbue(std::locale("fr_FR.utf8"));
        std::cout.imbue(std::locale("zh_Hans.utf8"));
        m_u = money::m_units::EUR;
    }
    long double val;
    s1 >> std::get_money(val);
    money m1(val, m_u);

    std::cout << "Choose the transfer currency: USD, EUR, GBP, CNY, RUB\n";
    std::cin >> str1;
    std::cout << std::showbase << std::put_money(m1.get_value(), false) << "-->";

    if (str1 == "USD") {
        std::cout.imbue(std::locale("en_US.UTF-8"));
        m_u = money::m_units::USD;
    }
    if (str1=="RUB") {
        std::cout.imbue(std::locale("ru_RU.utf8"));
        m_u = money::m_units::RUB;
    }
    if (str1=="GBP") {
        std::cout.imbue(std::locale("en_GB.utf8"));
        m_u = money::m_units::GBP;
    }
    if (str1=="CNY") {
        std::cout.imbue(std::locale("zh_Hans.utf8"));
        m_u = money::m_units::CNY;
    }
    if (str1=="EUR") {
        std::cout.imbue(std::locale("fr_FR.utf8"));
        m_u = money::m_units::EUR;
    }
    m1.change_unit_to(m_u);
    std::cout << std::showbase << std::put_money(m1.get_value(), false) << std::endl;
}
