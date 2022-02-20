#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <chrono>
#include <algorithm>
#include <iomanip>

#include <boost/multi_array.hpp>

template < auto N, typename Container, typename Forward_Iterator >
void fill_shape(const Container& container, Forward_Iterator shape)
{
	*shape = std::size(container);

	if constexpr (N > 1)
	{
		fill_shape < N - 1 >(*(std::begin(container)), ++shape);
	}
}

int main()
{
	const auto size_1 = 3U;
	const auto size_2 = 4U;
	const auto size_3 = 5U;

	std::vector < std::vector < std::vector < int > > > v(size_1,
		std::vector < std::vector < int > >(size_2,
			std::vector < int >(size_3, 0)));
	auto counter = 0;

	for (auto i = 0U; i < size_1; ++i)
	{
		for (auto j = 0U; j < size_2; ++j)
		{
			for (auto k = 0U; k < size_3; ++k)
			{
				(v[i][j][k] = ++counter);
			}
		}
	}

	std::vector < boost::multi_array < int, 3 >::index > shape(3, boost::multi_array < int, 3 >::index(0));
	//for (auto element : shape)
	//{
	//	std::cout << element << ' ';
	//}
	fill_shape < 3 >(v, std::begin(shape));
	boost::multi_array < int, 3 > multi_array(shape);
	for (auto element1 : multi_array)
	{
		for (auto element2 : element1)
		{
			for (auto& element3 : element2)
			{
				std::cout << element3 << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}