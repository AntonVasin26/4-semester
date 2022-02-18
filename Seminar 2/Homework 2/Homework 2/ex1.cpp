#include <vector>
#include <iostream>

int main()
{
	std::vector<int> v1;
	std::cout << "test 1 vector 1\n";
	std::cout << v1.capacity() << ";  ";
	for (int i = 0; i < 15; ++i)
	{
		v1.push_back(1);
		std::cout << v1.capacity() << ";  ";
	}
	std::cout << "\n\ntest 2 vector 1\n";
	v1.clear();
	std::cout << v1.capacity() << ";  ";
	for (int i = 0; i < 20; ++i)
	{
		v1.push_back(1);
		std::cout << v1.capacity() << ";  ";
	}
	std::cout << "\n\ntest 3 vector 1\n";
	v1.reserve(10);
	std::cout << v1.capacity() << ";  ";
	v1.reserve(30);
	std::cout << v1.capacity() << ";  ";
	std::cout << "\n\ntest 4 vector 2\n";
	std::vector<int> v2;
	std::cout << v2.capacity() << ";  ";
	v2.reserve(10);
	std::cout << v2.capacity() << ";  ";
	for (int i = 0; i < 20; ++i)
	{
		v2.push_back(1);
		std::cout << v2.capacity() << ";  ";
	}
	std::vector<double> v3;
	std::cout << "\n\ntest 5 vector 3\n";
	v3.push_back(4.345463);
	std::cout << v3.capacity() << ";  ";
	//v3.reserve(1000000000); - std::length_error
	//v3.reserve(300000000); - std::bad_alloc


	
}