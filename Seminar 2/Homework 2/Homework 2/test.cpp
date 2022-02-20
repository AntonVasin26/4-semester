#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <chrono>
#include <algorithm>


int main()
{
	std::vector<int> v1 = { 1,2,3,4 };
	std::array<int, 6> a1 = { 5,6,7,8 };
	for (auto i = 0; i < v1.size(); ++i)
	{
		std::cout << v1[i];
	}
	std::cout << '\n';
	for (auto i = 0; i < a1.size(); ++i)
	{
		std::cout << a1[i];
	}
	std::cout << '\n';
	v1.assign(a1.begin(), a1.end());
	for (auto i = 0; i < v1.size(); ++i)
	{
		std::cout << v1[i];
	}
	std::cout << '\n';

}