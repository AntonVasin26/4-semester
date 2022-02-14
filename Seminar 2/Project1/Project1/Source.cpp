#include <tuple>
#include <iostream>

int main()
{
	//std::tuple < int, double> t(42, 2.22);
	//tuple_size<>::value, typle_element<...>::type, tuple_cat(...),
	auto t = std::make_tuple(42, 1.23);
	std::cout << std::get < 0 > (t) << std::endl;
	int i;
	double d;

	std::tie(i, d) = t;
	std::tie(i, std::ignore) = t;

}