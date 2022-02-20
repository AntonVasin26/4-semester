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
	explicit Timer(std::string name) : n(name), m_begin(clock_t::now()), time(value(0)), flag(true)
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

	void print_mean_time(int quantity)
	{
		if (!flag)
		{
			std::cout << n << "(mean_time): " << std::chrono::duration_cast <value> (time + (clock_t::now() - m_begin)).count()/quantity << '\n';
		}
		else
		{
			std::cout << n << "(mean_time): " << std::chrono::duration_cast <value> (time).count() / quantity << '\n';
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
	std::vector<int> v1;
	v1.reserve(std::size(init_array));
	std::deque<int> q1;
	std::list<int> l1;
	std::forward_list<int> fl1;
	Timer<std::chrono::microseconds> t1("vector");
	Timer<std::chrono::microseconds> t2("array");
	Timer<std::chrono::microseconds> t3("deque");
	Timer<std::chrono::microseconds> t4("list");
	Timer<std::chrono::microseconds> t5("forward_list");
	int Number_of_passes = 10;
	for (auto j = 0; j < Number_of_passes; ++j)
	{
		for (auto i = 0; i < std::size(init_array); ++i)
		{
			init_array[i] = rand() % 1000;
		}

		v1.assign(init_array.begin(), init_array.end());
		q1.assign(init_array.begin(), init_array.end());
		l1.assign(init_array.begin(), init_array.end());
		fl1.assign(init_array.begin(), init_array.end());


		t1.play();
		std::sort(v1.begin(), v1.end());
		t1.stop();

		t2.play();
		std::sort(init_array.begin(), init_array.end());
		t2.stop();

		t3.play();
		std::sort(q1.begin(), q1.end());
		t3.stop();

		t4.play();
		//std::sort(l1.begin(), l1.end());
		l1.sort();
		t4.stop();

		t5.play();
		//std::sort(q1.begin(), q1.end());
		fl1.sort();
		t5.stop();
		t1.print_time();
		t2.print_time();
		t3.print_time();
		t4.print_time();
		t5.print_time();
	}

	t1.print_mean_time(Number_of_passes);
	t2.print_mean_time(Number_of_passes);
	t3.print_mean_time(Number_of_passes);
	t4.print_mean_time(Number_of_passes);
	t5.print_mean_time(Number_of_passes);
}