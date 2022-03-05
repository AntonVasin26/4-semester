#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <chrono>
#include <random>

void print(std::vector<int> v1)
{
	std::copy(std::cbegin(v1), std::cend(v1),
		std::ostream_iterator < int >(std::cout, " "));
	std::cout << '\n';
	/*for (auto element : v1)
	{
		std::cout << element << ' ';
	}
	std::cout << '\n';*/
}


int main()
{
	std::cout << "1)\n";
	std::vector<int> v1(1);
	v1.reserve(30);

	std::cout << "2)\n";
	std::copy(std::istream_iterator < int >(std::cin),
		std::istream_iterator < int >(),
		std::back_inserter(v1));
	print(v1);

	std::cout << "7)\n";
	auto f = [](int n)
	{
		if (n == 1) return 0;
		if (n == 2) return 1;
		if (n % 2 == 0) return 0;
		for (int i = 3; i <= sqrt(abs(n)); i += 2)
			if (n % i == 0)  return 0;
		return 1;
	};
	auto simple = std::find_if(std::begin(v1), std::end(v1), f);
	if (simple < std::end(v1))
		std::cout << "prime_number: " << *simple << '\n';
	else
		std::cout << "prime_number: Not found\n";
}