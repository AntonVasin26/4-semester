#include <chrono>
#include <iostream>

template <typename value >
class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using interval = clock_t::duration;
	Timer() : m_begin(clock_t::now()), time(value(0))
	{}
	void start()
	{
		m_begin = clock_t::now();
		flag = false;
		time = std::chrono::microseconds(0);
	};

	void play()
	{
		if (flag == true)
		{
			m_begin = clock_t::now();
			flag = false;
		}
	};

	void stop()
	{
		if (flag == false)
		{
			m_end = clock_t::now();
			time += (m_end - m_begin);
			flag = true;
		}
	};


	void print_time()
	{
		if (flag == false)
		{
			m_end = clock_t::now();
			std::cout << std::chrono::duration_cast <value> (m_end - m_begin).count() << '\n';
			m_begin = m_end;
		}
		else
		{
			std::cout << std::chrono::duration_cast <value> (time).count() << '\n';
		}
	}

	~Timer() noexcept
	{}
private:
	time_point_t m_begin;
	time_point_t m_end;
	interval time;
	bool flag = false;
};

int main(int argc, char** argv)
{
	{
		Timer<std::chrono::microseconds> t1;
		Timer<std::chrono::milliseconds> t2;
		Timer<std::chrono::seconds> t3;
		auto c = 1.0;
		t1.start();
		for (auto j = 0; j < 3; ++j)
		{
			t2.play();
			for (auto i = 0; i < 10000000; ++i)
			{
				t3.play();
				c += 1.01;
				c = std::pow(c, 1.01);
				t3.stop();
			}
			t2.stop();
			t2.print_time();
		}
		t1.print_time();
		t2.print_time();
		t3.print_time();
	}

}
