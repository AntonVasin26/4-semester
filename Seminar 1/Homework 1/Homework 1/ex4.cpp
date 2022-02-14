#include <chrono>
#include <iostream>

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

int main(int argc, char** argv)
{
	{
		Timer<std::chrono::microseconds> t1("clock1");
		Timer<std::chrono::milliseconds> t2("clock2");
		Timer<std::chrono::seconds> t3("clock3");
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
