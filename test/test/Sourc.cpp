#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <time.h>

template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

void UNIXTimeToDate(char* buf, int unixtime)
{
	time_t t = unixtime;
	struct tm* tm = localtime(&t);
	char tmp[20];
	strftime(tmp, sizeof(tmp), "%d/%m/%Y %H:%M:%S", tm);// нуу так мне удобнее ))
	strcpy(buf, tmp);
	return;
}



void view_directory(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		char* stst = new char[50];
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();

			auto p = entry.path();
			auto ftime = std::filesystem::last_write_time(p);
			int unix = to_time_t<std::chrono::time_point<std::chrono::file_clock>>(ftime);

			UNIXTimeToDate(stst, 1493768871);
			std::cout << file_name << ' ' << stst << std::endl;
		}
		delete[] stst;
	}
}

int main(int argc, char** argv)
{
	system("chcp 1251");

	view_directory(std::filesystem::current_path());

	system("pause");

	return EXIT_SUCCESS;
}
