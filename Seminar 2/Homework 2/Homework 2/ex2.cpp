#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <chrono>
#include <algorithm>

template <typename value >
class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	explicit Timer(std::string name) : n(name), m_begin(clock_t::now()), time(value(0))
	{}
	void start()
	{
		m_begin = clock_t::now();
		flag = false;
		time = value(0);
	};

	void play()
	{
		if (flag)
		{
			m_begin = clock_t::now();
			flag = false;
		}
	};

	void stop()
	{
		if (!flag)
		{
			time += (clock_t::now() - m_begin);
			flag = true;
		}
	};


	void print_time()
	{
		if (!flag)
		{
			std::cout << n << ": " << std::chrono::duration_cast <value> (time + (clock_t::now() - m_begin)).count() << '\n';
		}
		else
		{
			std::cout << n << ": " << std::chrono::duration_cast <value> (time).count() << '\n';
		}
	}

	~Timer() noexcept
	{
		if (!flag)
		{
			time += (clock_t::now() - m_begin);
		}
		std::cout << n << ": " << std::chrono::duration_cast <value> (time).count() << ";   Timer delete\n";
	}
private:
	std::string n;
	time_point_t m_begin;
	clock_t::duration time;
	bool flag = false;
};


int main()
{
	std::array<int, 100000> init_array;
	for (auto i = 0; i < 100000; ++i)
	{
		init_array[i] = rand() % 1000;
	}
	std::vector<int> v1(init_array.begin(), init_array.end());
	std::deque<int> q1(init_array.begin(), init_array.end());
	std::list<int> l1(init_array.begin(), init_array.end());
	std::forward_list<int> fl1(init_array.begin(), init_array.end());
	std::forward_list<int> fl2(init_array.begin(), init_array.end());

	Timer<std::chrono::microseconds> t1("vector");
	t1.start();
	std::sort(v1.begin(), v1.end());
	t1.print_time();

	Timer<std::chrono::microseconds> t2("array");
	t2.start();
	std::sort(init_array.begin(), init_array.end());
	t2.print_time();

	Timer<std::chrono::microseconds> t3("deque");
	t3.start();
	std::sort(q1.begin(), q1.end());
	t3.print_time();

	Timer<std::chrono::microseconds> t4("list");
	t4.start();
	//std::sort(l1.begin(), l1.end());
	l1.sort();
	t4.print_time();

	auto iter = fl1.begin();
	Timer<std::chrono::microseconds> t5("forward_list");
	t5.start();
	//std::sort(q1.begin(), q1.end());
	fl1.sort();
	t5.print_time();




}