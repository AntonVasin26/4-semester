#pragma once
#include <iostream>
#include <chrono>

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
			std::cout << n << "(mean_time): " << std::chrono::duration_cast <value> (time + (clock_t::now() - m_begin)).count() / quantity << '\n';
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