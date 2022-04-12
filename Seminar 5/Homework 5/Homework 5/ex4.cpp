#include <iostream>
#include <regex>
#include <string>
#include <fstream>

bool leap_year(int year)
{
	return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

bool correct_date_time(std::string date)
{
	if (date[4] == '\.')
	{
		int year = std::stoi(date.substr(0, 4));
		int month = std::stoi(date.substr(5, 2));
		int day = std::stoi(date.substr(8, 2));
		if (!leap_year(year) && month == 2 && day == 29)
			return false;
	}
	return true;
}


int main()
{
	std::cout << "ex4\n\n";

	std::regex pattern4(R"((?:\d{4})\.(?:(?:(?:0[13578]|1[02])\.(?:[012][0-9]|3[01]))|(?:(?:0[469]|11)\.(?:[012][0-9]|30))|(?:02\.(?:[012][0-9])))|(?:(?:2[0-3]|[01][0-9])(?::[0-5][0-9]){2}))");
	//.......................year.....(..(......month with 31 days..................)|(......month with 30 days..........)|(......february.......)|...time.......................................
	
	std::smatch matches;
	std::fstream fin("ex4_test_text.txt", std::ios::in);
	std::string code{
		std::istreambuf_iterator < char >(fin),
		std::istreambuf_iterator < char >() };
	std::sregex_iterator begin(code.cbegin(), code.cend(), pattern4);
	std::sregex_iterator end;

	std::for_each(begin, end, [](const std::smatch& m)
		{
			for (std::size_t i = 0; i < m.size(); ++i)
			{
					std::cout << m[i] << " | ";
					if (!correct_date_time(m[i]))
					{
						std::cout << " Incorrect date";
					}
			}

			std::cout << std::endl;
		});
}

/*std::regex pattern(R"((?:(?:[01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9])|(?:(?:[0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3})\.(?:(?:(?:0[13578]|1[02])\.(?:0[1-9]|[12][0-9]|3[01]))|(?:(?:0[469]|11)\.(?:0[1-9]|[12][0-9]|30))|(?:02\.(?:0[1-9]|[1][0-9]|2[0-8]))))|(?:(?:(?:[0-9]{2})(?:0[48]|[2468][048]|[13579][26])|(?:(?:0[48]|[2468][048]|[3579][26])00))\.02\.29))");
*/
//Output all the times and dates in the file one after another,
//taking into account leap years, but you need to write zeros
//before the numbers.

//std::regex pattern3(R"((?:(?:[01]?[0-9]|2[0-3]):[0-5]?[0-9]:[0-5]?[0-9])|(?:(?:(?:[0-9]{0,2})(?:0[48]|[2468][048]|[13579][26])|(?:(?:0?[48]|[2468][048]|[13579][26])00))\.0?2\.29)|(?:(?:(?:[0-9]{3})?[1-9]|(?:[0-9]{2})?[1-9][0-9]{1}|(?:[0-9]{1})?[1-9][0-9]{2}|[1-9][0-9]{3})\.(?:(?:(?:0?[13578]|1[02])\.(?:[12][0-9]|3[01]|0?[1-9]))|(?:(?:0?[469]|11)\.(?:[12][0-9]|30|0?[1-9]))|(?:0?2\.(?:[1][0-9]|2[0-8]|0?[1-9])))))");
//final version
