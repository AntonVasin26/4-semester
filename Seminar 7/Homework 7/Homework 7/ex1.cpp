#include <iostream>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <algorithm>
#include <iterator>
#include <random>
#include "Timer.hpp"
#include <vector>


long long int counterr(long long int n, long long int seed)
{
	std::mt19937_64 mt(static_cast <unsigned int> (seed));
	std::uniform_int_distribution<long long int> unif(-1000000, 1000000);
	long long int count = 0;
	long long int x;
	long long int y;
	for (auto i = 0; i < n; i++)
	{
		x = unif(mt);
		y = unif(mt);
		if (std::pow(x, 2) + std::pow(y, 2) < std::pow(10, 12))
		{
			count++;
		}
	}
	return count;
}
double cal_pi(long long int n,
	long long int seed = std::chrono::system_clock::now().time_since_epoch().count())
{
	auto count = counterr(n, seed);
	double pi = static_cast<double>(count) * 4.0 / static_cast<double>(n);
	return pi;
}

double par_cal_pi(long long int n)
{
	auto p = std::thread::hardware_concurrency(); //16

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 mt(static_cast <unsigned int> (seed));
	std::uniform_int_distribution<unsigned long long int> unif(0, ULLONG_MAX);

	long long int sum = 0;
	std::vector < std::future < long long int > > futures(16);
	std::vector < std::thread >	threads(16);
	for (auto i = 0U; i < 16; i++)
	{
		int m = n / p;
		//std::packaged_task <int(int, int) > task([](int a, int b) {return std::pow(a, b);  });
		std::packaged_task < long long int(long long int, long long int) > task(counterr(m,unif(mt)) );
		threads[i] = std::thread(std::move(task), m, unif(mt));
		futures[i] = task.get_future();
	}
	
	//for (auto i = 0; i < 16; i++)
	//{
	//	sum += futures[i].get();
	//}
	auto pi = static_cast<double>(sum) * 4.0 / static_cast<double>(n);
	return pi ;
}

int main()
{
	Timer<std::chrono::seconds> t1("cal_pi");
	std::cout << std::thread::hardware_concurrency() << std::endl; //16
	//t1.start();
	//std::cout << cal_pi(std::pow(10, 8)) << std::endl;
	//t1.stop();
	//t1.print_time();//43 secod
	t1.start();
	std::cout << par_cal_pi(std::pow(10, 7)) << std::endl;
	t1.stop();
	t1.print_time();//4 second




}