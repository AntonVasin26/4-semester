#include <iostream>
#include <set>
#include <vector>
#include "Timer.hpp"
#include <algorithm>
#include <iterator>
#include <random>

int main()
{
	Timer<std::chrono::microseconds> t1("Set");
	Timer<std::chrono::microseconds> t2("Vector");
	std::vector<int> init_v;
	std::vector<int> v1;
	int v_length = 100000;
	init_v.reserve(v_length);
	v1.reserve(v_length);

	for (int i = 0; i < v_length; ++i)
	{
		init_v.push_back(i);
	}
	std::set <int> s1;
	for (auto element : init_v)
	{
		s1.insert(element);
	}
	s1.clear();

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(init_v.begin(), init_v.end(), g);
	for (auto j = 1; j < 10; ++j)
	{
		t1.play();
		for (auto element : init_v)
		{
			s1.insert(element);
		}
		t1.stop();
		s1.clear();

		t2.play();
		v1.assign(std::begin(init_v), std::end(init_v));
		std::sort(init_v.begin(), init_v.end());
		t2.stop();
		v1.clear();
	}
	t1.print_mean_time(10);
	t2.print_mean_time(10);
	//with a vector 8 times faster
}