#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include <numeric>
#include <chrono>
#include <string>


void print(std::vector<int>& v1)
{
	std::copy(std::cbegin(v1), std::cend(v1),
		std::ostream_iterator < int >(std::cout, " "));
	std::cout << '\n';
}

void print(std::vector< std::pair<unsigned int, int> >& v1)
{
	for (auto elm : v1)
	{
		std::cout << "(" << elm.first << "; " << elm.second << "); ";
	}
	std::cout << '\n';
}


std::vector< std::pair<unsigned int, unsigned int> > find_indexs(int sum, std::vector< std::pair<unsigned int, int> > &list)
{
	unsigned int i_l = 0;
	unsigned int i_r = std::size(list) - 1;
	std::vector< std::pair<unsigned int, unsigned int> > output;
	while (i_l < i_r) 
	{
		if (list[i_l].second + list[i_r].second > sum)
		{
			i_r--;
		}

		else if (list[i_l].second + list[i_r].second < sum)
		{
			i_l++;
		}

		else
		{
			if (list[i_l].second == list[i_r].second)
			{
				unsigned int count_equal = i_r - i_l - 1;
				for (unsigned int j_l = i_l; j_l <= i_l+ count_equal; j_l++)
				{
					for (unsigned int j_r = j_l+1; j_r <= i_r ; j_r++)
					{
						output.push_back(std::make_pair(list[j_l].first, list[j_r].first));
					}
				}
			}
			else
			{
				unsigned int count_equal_left = 0;
				unsigned int count_equal_right = 0;
				while (i_l < i_r && list[i_l].second == list[i_l + 1].second)
				{
					count_equal_left++;
					i_l++;
				}
				while (i_l < i_r && list[i_r].second == list[i_r - 1].second)
				{
					count_equal_right++;
					i_r--;
				}
				for (unsigned int j_l = i_l - count_equal_left; j_l <= i_l; j_l++)
				{
					for (unsigned int j_r = i_r; j_r <= i_r + count_equal_right; j_r++)
					{
						unsigned int i_1 = list[j_l].first;
						unsigned int i_2 = list[j_r].first;
						if (i_1 > i_2 ) std::swap(i_1, i_2);
						output.push_back(std::make_pair(i_1, i_2));
					}
				}
			}

			
			i_l++;
			i_r--;
		}
	}
	return output;
}


int main()
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::vector<int> input_list = { 2, 29 };
	const unsigned int l_lengh = std::size(input_list);
	int find_sum = 4;
	std::default_random_engine dre_1(static_cast <unsigned int> (seed));
	std::shuffle(std::begin(input_list), std::end(input_list), dre_1);

	//const unsigned int l_lengh = 100;
	//std::vector<int> input_list(l_lengh);
	//std::default_random_engine dre_2(static_cast <int> (seed));
	//std::uniform_int_distribution <int> uid(-100, 100);
	//std::generate(std::begin(input_list), std::end(input_list), [&uid, &dre_2]() {return uid(dre_2); });
	//int find_sum = uid(dre_2);


	std::cout << "input list: ";
	print(input_list);
	std::cout << "find sum: " << find_sum << '\n';


	std::vector< std::pair<unsigned int, int> > work_list(l_lengh);
	int i = 0;
	std::transform(std::begin(input_list), std::end(input_list), std::begin(work_list), [&i](int x) {return std::make_pair(i++, x);});
	print(work_list);

	std::cout << '\n';

	auto direct_sort = [](std::pair<int, int> x, std::pair <int, int> y) { return x.second < y.second; };
	std::sort(std::begin(work_list), std::end(work_list), direct_sort);
	print(work_list);

	std::cout << '\n';

	
	auto answer = find_indexs(find_sum, work_list);
	auto direct_sort_answer = [](std::pair<unsigned int, unsigned int> x, std::pair <unsigned int, unsigned int> y) { return x.first < y.first; };
	std::sort(std::begin(answer), std::end(answer), direct_sort_answer);
	std::cout << "answer: ";
	for (auto elm : answer)
	{
		std::cout << "(" << elm.first << "; " << elm.second << "); ";
	}
}
