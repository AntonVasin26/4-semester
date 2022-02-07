#include <chrono>
#include <iostream>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	Timer() : m_begin(clock_t::now())
	{}
	~Timer() noexcept
	{
		std::cout << std::chrono::duration_cast <
			std::chrono::microseconds> (clock_t::now() - m_begin).count() << "microseconds" << std::endl;
	}
private:
	time_point_t m_begin;
};

int main(int argc, char** argv)
{
	//std::chrono::duration <int> a(20);
	//std::chrono::duration <double, std::ratio <60> > b(0.5);
	//std::chrono::duration <

	//std::chrono::seconds a(20);
	//std::chrono::hours b(24);
	//std::chrono::milliseconds c(17);
	//c += a - b;
	//--c;
	//c *= 2;
	//std::cout << c.count() << std::endl;
	//std::cout <<
	{
		Timer t;

		auto c = 1.0;
		for (auto i = 0; i < 10000000; ++i)
		{
			c += 1.23;
			c = std::pow(c, 1.01);
		}
	}

}