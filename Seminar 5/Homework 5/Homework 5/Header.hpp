#pragma once
#include <vector>
#include <string>
#include <typeinfo>
#include <map>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <boost/locale.hpp>

#include <Windows.h> 

class money
{
public:
	enum class m_units
	{
		RUB,
		EUR,
		GBP,
		USD,
		CNY,
	};
	money(long double value) :
		m_value(value), m_unit(money::m_units::RUB)
	{}
	money(long double value, const money::m_units& unit) :
		m_value(value), m_unit(unit)
	{}
	void change_unit_to(const money::m_units& unit)
	{
		switch (m_unit)
		{
		case money::m_units::EUR:
			m_value *= EUR;
			break;
		case money::m_units::USD:
			m_value *= USD;
			break;
		case money::m_units::GBP:
			m_value *= GBP;
			break;
		case money::m_units::CNY:
			m_value *= 16.36;
			break;
		case money::m_units::RUB:
			break;
		default:
			break;
		}

		switch (unit)
		{
		case money::m_units::RUB:
			break;
		case money::m_units::EUR:
			m_value /= EUR;
			break;
		case money::m_units::USD:
			m_value /= USD;
			break;
		case money::m_units::GBP:
			m_value /= GBP;
			break;
		case money::m_units::CNY:
			m_value /= CNY;
			break;
		default:
			break;
		}
		m_unit = unit;
	}

	const auto const get_value()
	{
		return m_value;
	}

	const auto const get_unit()
	{
		return m_unit;
	}

	void print()
	{
		std::cout << '\n' << std::scientific << m_value;
	}

private:
	long double m_value;
	m_units m_unit;
	static inline const long double EUR = 114.7;
	static inline const long double GBP = 137.7;
	static inline const long double USD = 103.2;
	static inline const long double CNY = 16.36;
};