#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <time.h>
#include <unordered_map>

std::string get_ext(const std::filesystem::path& file) {
	std::string name = file.filename().string();
	size_t pos = name.rfind('.');
	if (pos == SIZE_MAX) return "";
	return name.substr(pos + 1, std::string::npos);
}

std::string get_type(const std::filesystem::path& file)
{
	std::string ext = get_ext(file);
	std::unordered_map <std::string, std::string> type = {
		{"drv", "system file"},
		{"sys", "system file"},
		{"exe", "system file"},
		{"txt", "text file"},
		{"rtf", "text file"},
		{"doc", "text file"},
		{"docx", "text file"},
		{"odt", "text file"},
		{"json", "text file"},
		{"bmp", "graphic file"},
		{"gif", "graphic file"},
		{"jpg", "graphic file"},
		{"tif", "graphic file"},
		{"png", "graphic file"},
		{"pds", "graphic file"},
		{"htm", "Web page"},
		{"html", "Web page"},
		{"wav", "audio file"},
		{"mp3", "audio file"},
		{"midi", "audio file"},
		{"kar", "audio file"},
		{"ogg", "audio file"},
		{"avi", "video file"},
		{"mpeg", "video file"},
		{"zip", "arñhive file"},
		{"xls", "spreadsheet"},
		{"ods", "spreadsheet"},
		{"cpp", "text file(for_code)"},
	};
	if (type.find(ext) == type.end()) return "other extension";
	return type[ext];
}

std::string get_unix_type(std::filesystem::path& file)
{
	using namespace std::filesystem;
	if (is_directory(file)) return "directory";
	if (is_regular_file(file)) return "regular file";
	if (is_character_file(file)) return "character device";
	if (is_block_file(file)) return "block device";
	if (is_socket(file)) return "named IPC socket";
	if (is_fifo(file)) return "named pipe";
	if (is_symlink(file)) return "symbolic link";
	return "other file";
}

template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

void view_directory(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path))
	{
		if (std::filesystem::is_directory(path))
		{
			std::cout << "directory: " << path.filename().string() << std::endl;
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				auto file = entry.path();
				auto file_name = file.filename().string();
				auto ftime = std::filesystem::last_write_time(file);
				auto unix = to_time_t<std::chrono::time_point<std::chrono::file_clock>>(ftime);
				std::cout << file_name << '(' << get_unix_type(file) << "; " << get_type(file) << ") " << unix << std::endl;
			}
		}
		else
		{
			auto file = path;
			auto file_name = file.filename().string();
			auto ftime = std::filesystem::last_write_time(file);
			auto unix = to_time_t<std::chrono::time_point<std::chrono::file_clock>>(ftime);
			std::cout << file_name << '(' << get_unix_type(file) << "; " << get_type(file) << ") " << unix << std::endl;
		}
	}
	else std::cout << "file not found" << std::endl;
}

int main(int argc, char** argv)
{
	system("chcp 1251");

	view_directory(std::filesystem::current_path());
	std::cout << std::endl;
	view_directory(std::filesystem::current_path() / "result.txt");
	std::cout << std::endl;
	view_directory(std::filesystem::current_path() / "outfit.txt"); //not found

	system("pause");

	return EXIT_SUCCESS;
}