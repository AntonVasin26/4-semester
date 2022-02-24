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
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(init_v.begin(), init_v.end(), g);


	t1.start();
	std::set <int> s1;
	for (auto element : init_v)
	{
		s1.insert(element);
	}
	t1.stop();
	

	for (auto j = 1; j < 10; ++j)
	{
		s1.clear();
		t1.start();
		for (auto element : init_v)
		{
			s1.insert(element);
		}
		t1.stop();
		t1.print_time();

		v1.clear();
		t2.start();
		v1.assign(std::begin(init_v), std::end(init_v));
		std::sort(init_v.begin(), init_v.end());
		t2.stop();
		t2.print_time();
	}
}