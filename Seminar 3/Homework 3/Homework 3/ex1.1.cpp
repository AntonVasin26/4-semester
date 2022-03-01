#include <iostream>
#include <set>
#include <vector>
#include "Timer.hpp"
#include <algorithm>
#include <iterator>
#include <random>

int main()
{
	std::vector<int> init_v;
	const int v_length = 100000;
	init_v.reserve(v_length);

	for (int i = 0; i < v_length; ++i)
	{
		init_v.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(init_v.begin(), init_v.end(), g);

	const int N_of_repetion = 10;
	Timer<std::chrono::microseconds> t1("Set");
	Timer<std::chrono::microseconds> t2("Vector");
	for (auto j = 0; j <= N_of_repetion; ++j)
	{
		std::set <int> s1;
		std::vector<int> v1;
		v1.reserve(v_length);
		if (j != 0)
		{
			t1.play();
		}
		for (auto element : init_v)
		{
			s1.insert(element);
		}
		t1.stop();
		if (j != 0)
		{
			t2.play();
		}
		v1.assign(std::begin(init_v), std::end(init_v));
		std::sort(init_v.begin(), init_v.end());
		t2.stop();

	}
	t1.print_mean_time(N_of_repetion);
	t2.print_mean_time(N_of_repetion);
}