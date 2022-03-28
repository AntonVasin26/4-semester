#include <iterator>
#include <fstream>
#include <string>

void erase_comments(std::string& code);

int main(int argc, char** argv)
{
	std::fstream fin("test.txt", std::ios::in);

	std::string code{
		std::istreambuf_iterator < char >(fin),
		std::istreambuf_iterator < char >() };

	erase_comments(code);

	std::fstream fout("result.txt", std::ios::out);

	fout << code;

	system("pause");

	return EXIT_SUCCESS;
}

void erase_comments(std::string& code)
{
	for (auto current = std::begin(code); current != std::end(code); ++current)
	{
		if (*current == '"')
		{
			for (auto simbol = ++current; simbol != std::end(code); ++simbol)
			{
				if (*simbol == '\\')
					++simbol;
				else if (*simbol == '"')
				{
					current = ++simbol;
					break;
				}
			}
		}
		if (*current == '/')
		{
			if (*std::next(current) == '/')
			{
				for (auto simbol = current; simbol != std::end(code) && *simbol != '\n';)
					code.erase(simbol);
			}
			else if (*std::next(current) == '*')
			{
				for (auto simbol = current; !(*simbol == '*' && *std::next(simbol) == '/') && simbol != std::end(code);)
					code.erase(simbol);
				code.erase(current);
				code.erase(current);

			}
		}
		if (current == std::end(code))
		{
			break;
		}
	}
}