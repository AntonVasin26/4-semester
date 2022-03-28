#include <iostream>
#include <thread>
#include <future>

void F(int x)
{
	std::cout << "Hello!\n" << x << '\n';
}

int main(int ardc, char** argv)
{
	//std::cout << std::thread::hardware_concurrency() << std::endl;
	//int x = 42;

	//std::thread t(F, x);

	//t.join();//- 1 раз
	//t.detach();// - фоновая задача 1)while true 2) Опастность С ссылками
	// 
	// 
	// 
	//std::future <int> result = std::async(std::launch::async/*deferred*/, []() {return 42; });
	//std::cout << result.get() << std::endl; //wait, valid


	std::packaged_task < int()> task([]() {return 42; });
	std::future <int> result = task.get_future();
	std::thread(std::move(task)).detach();
}