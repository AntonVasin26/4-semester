#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <chrono>
#include <random>

void print(std::vector<int>& v1)
{
	std::copy(std::cbegin(v1), std::cend(v1),
		std::ostream_iterator < int >(std::cout, " "));
	std::cout << '\n';
}


int main()
{
	std::cout << "1)\n";
	std::vector<int> v1(10);
	v1.reserve(30);
	std::iota(std::begin(v1), std::end(v1), 1);

	print(v1);

	std::cout << "2)\n";
	std::copy(std::istream_iterator < int >(std::cin),
				std::istream_iterator < int >(),
				std::back_inserter(v1));
	print(v1);

	std::cout << "3)\n";
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine dre(static_cast <unsigned int> (seed));
	std::shuffle(std::begin(v1), std::end(v1), dre);
	print(v1);

	std::cout << "4)\n";
	std::sort(std::begin(v1), std::end(v1));
	auto n_end1 = std::unique(std::begin(v1), std::end(v1));
	print(v1);
	v1.erase(n_end1, std::end(v1));
	print(v1);

	std::cout << "5)\n";
	auto c = std::count_if(std::begin(v1), std::end(v1), [](int i) {return bool(i % 2); });
	std::cout << "number of odd: " << c << '\n';

	std::cout << "6)\n";
	auto p1 = std::minmax_element(std::begin(v1), std::end(v1));
	std::cout << "min: " << *(p1.first) << " max: " << *(p1.second) << '\n';

	std::cout << "7)\n";
	auto f =[](int n)
	{	
		if (n == 1) return 0;
		if (n == 2) return 1;
		if (n % 2 == 0) return 0;
		for (int i = 3; i <= sqrt(abs(n)); i+=2)
			if (n % i == 0)  return 0;
		return 1;
	};
	auto simple = std::find_if(std::begin(v1), std::end(v1), f);
	if (simple < std::end(v1))
		std::cout << "prime_number: " << *simple << '\n';
	else
		std::cout << "prime_number: Not found\n";

	std::cout << "8)\n";
	std::for_each(std::begin(v1), std::end(v1), [](int& n) {n = pow(n,2); });
	print(v1);

	std::cout << "9)\n";
	std::vector<int> v2(std::size(v1));
	std::uniform_int_distribution <unsigned int> uid(0, 100);
	std::generate(std::begin(v2), std::end(v2), [&uid, &dre]() {return uid(dre);});
	print(v2);

	std::cout << "10)\n";
	auto sum = std::accumulate(std::begin(v2), std::end(v2), 0);
	std::cout << "sum: " << sum << '\n';

	std::cout << "11)\n";
	std::fill_n(std::begin(v2), 3, 1);
	print(v2);

	std::cout << "12)\n";
	std::vector <int> v3(std::size(v2));
	std::transform(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v3), std::minus());
	print(v3);

	std::cout << "13\n"; 
	std::replace_if(std::begin(v3), std::end(v3), [](int x) {return x < 0; }, 0);
	print(v3);

	std::cout << "14)\n";
	auto n_end2 = std::remove_if(std::begin(v3), std::end(v3), [](int x) { return x==0; });
	v3.erase(n_end2, std::end(v3));
	print(v3);

	std::cout << "15)\n";
	std::reverse(std::begin(v3), std::end(v3));
	print(v3);

	std::cout << "16)\n";
	std::partial_sort(std::begin(v3), std::next(std::begin(v3), 3), std::end(v3));
	print(v3);

	std::cout << "17)\n";
	std::sort(std::begin(v1), std::end(v1));
	print(v1);
	std::sort(std::begin(v2), std::end(v2));
	print(v2);

	std::cout << "18)\n";
	std::vector<int> v4(std::size(v1) + std::size(v2));
	std::merge(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::begin(v4));
	print(v4);

	std::cout << "19)\n";
	auto p2 = std::equal_range(std::begin(v4), std::end(v4), 1);
	std::cout << "lower_bound: " << p2.first - std::begin(v4) << "   upper_bound: " << p2.second - std::begin(v4)<< '\n';

	std::wcout << "20)\n";
	print(v1);
	print(v2);
	print(v3);
	print(v4);
}