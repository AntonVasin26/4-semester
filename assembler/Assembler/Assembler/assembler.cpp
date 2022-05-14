#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>

#include <windows.h>

class Timer
{
private:

	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;

public:

	template < typename Name, typename Enable =
		std::enable_if_t < std::is_convertible_v < Name, std::string > > >
	explicit Timer(Name&& name, std::ostream& stream) :
		m_name(std::forward < Name >(name)), m_stream(stream), m_begin(clock_t::now())
	{
		initialize();
	}

	~Timer() noexcept
	{
		try
		{
			uninitialize();
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	void initialize()
	{
		m_stream << "Timer \"" << m_name << "\" launched ... " << std::endl << std::endl;
	}

	void uninitialize()
	{
		elapsed();
	}

public:

	void elapsed() const
	{
		auto end = clock_t::now();

		m_stream << "Timer \"" << m_name << "\" elapsed " << std::setprecision(6) << std::fixed <<
			static_cast <double> (std::chrono::duration_cast <std::chrono::microseconds>
				(end - m_begin).count()) / 1'000'000.0 << " (seconds)" << std::endl << std::endl;
	}

private:

	std::string m_name;
	time_point_t m_begin;

private:

	std::ostream& m_stream;
};

// =============================================================================

// Call conventions:
// __cdecl
// __pascal
// __stdcall
// __fastcall

void __stdcall print(const char * message) // __cdecl
{
	printf("%s", message);
}

// =============================================================================

void function_hello_world_from_console()
{
	const char * message = "Hello, world from ASM!\n\n";

	__asm
	{
		push message

		call print

		//pop message
	}
}

// =============================================================================

void function_hello_world_from_window()
{
	const char * message = "Hello, world from ASM!\n\n";

	const char * window  = "window";

	__asm
	{
		push MB_OK
		push window
		push message

		call GetForegroundWindow

		push eax

		call MessageBoxA
	}
}

// =============================================================================

int function_computation_test_cpp()
{
	int c = 0;

	{
		Timer t("C++", std::cout);

		int a = 1;
		int b = 1;

		for (int i = 0; i < 10'000'000; ++i)
		{
			for (int j = 0; j < 25; ++j)
			{
				c = a + b;
				a = b;
				b = c;
			}

			a = 1;
			b = 1;
		}
	}

	return c;
}

// =============================================================================

int function_computation_test_asm()
{
	int c = 0;
	
	{
		Timer t("ASM", std::cout);

		__asm
		{
			mov eax, 1;
			mov ebx, 1;

			mov esi, 10000000;

		loop_1:

			mov edi, 25;

		loop_2:

			mov ecx, eax;
			add ecx, ebx;
			mov eax, ebx;
			mov ebx, ecx;

			dec edi;
			jnz loop_2;

			mov eax, 1;
			mov ebx, 1;

			dec esi;
			jnz loop_1;

			mov c, ecx;
		}
	}

	return c;
}

// =============================================================================

double function_super_scalar_multiplication_cpp(double * a, double * b, std::size_t size)
{
	auto result_cpp = 0.0;

	{
		Timer t("C++", std::cout);

		for (auto i = 0U; i < size; ++i)
		{
			result_cpp += (std::pow(a[i], 8.0) * std::pow(b[i], 8.0));
		}
	}

	return result_cpp;
}

// =============================================================================

double function_super_scalar_multiplication_asm(double * a, double * b, std::size_t size)
{
	auto result_asm = 0.0;

	{
		const auto s = size; // ?

		Timer t("ASM", std::cout);

		__asm
		{
			mov eax, a;
			mov ebx, b;
			mov ecx, s;
			mov edx, 0;

			fldz;

		loop_1:
			
			fld qword ptr [eax + 8 * edx];

			mov esi, 3;

		loop_pow_1:

			fld st(0);
			fmul;

			dec esi;
			jnz loop_pow_1;

			fld qword ptr [ebx + 8 * edx];

			mov edi, 3;

		loop_pow_2:

			fld st(0);
			fmul;

			dec edi;
			jnz loop_pow_2;

			fmul;
			fadd;

			inc edx;
			cmp edx, ecx; // ?
			jl loop_1;

			fstp result_asm;
		}
	}

	return result_asm;
}

// =============================================================================

void test_1()
{
	std::cout << "Test 1 launched ... " << std::endl << std::endl;

	function_hello_world_from_console();
	function_hello_world_from_window();
}

void test_2()
{
	std::cout << "Test 2 launched ... " << std::endl << std::endl;

	const auto result_cpp = function_computation_test_cpp();
	const auto result_asm = function_computation_test_asm();

	std::cout << "Result C++: " << result_cpp << std::endl;
	std::cout << "Result ASM: " << result_asm << std::endl << std::endl;
}

void test_3()
{
	std::cout << "Test 3 launched ... " << std::endl << std::endl;

	const auto size = 10'000'000U;

	double * a = new double[size];
	double * b = new double[size];

	for (auto i = 0U; i < size; ++i)
	{
		a[i] = i * 0.000000042;
		b[i] = i * 0.000000042;
	}

	const auto result_cpp = function_super_scalar_multiplication_cpp(a, b, size);
	const auto result_asm = function_super_scalar_multiplication_asm(a, b, size);

	std::cout << "Result C++: " << std::setprecision(12) << std::fixed << result_cpp << std::endl;
	std::cout << "Result ASM: " << std::setprecision(12) << std::fixed << result_asm << std::endl << std::endl;

	delete[] a;
	delete[] b;
}

// =============================================================================

int main(int argc, char** argv)
{
	test_1();
	test_2();
	test_3();	

	system("pause");

	return EXIT_SUCCESS;
}