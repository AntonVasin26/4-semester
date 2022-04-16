#include <vector>
#include <iostream>


int main()
{
	std::vector<int> v;
	for (auto i = 0; i < 10; ++i) v.push_back(i);
	std::cout << "vec size: " << v.size() << '\n';
	v.erase(v.begin(), v.begin() + 3);
	for (auto i : v)
	{
		std::cout << i << '\n';
	}

	std::cout << "vec size: " << v.size();

}