#include <iostream>

#include "python.hpp"

int main (int arc, char ** argv)
{
	try
	{
		Python python;

		boost::python::exec("from main import f", python.global(), python.global());

		auto function = python.global()["f"](100);

		std::string message = boost::python::extract < std::string > (function);

		std::cout << message << std::endl;
	}
	catch (const boost::python::error_already_set &)
	{
		std::cerr << Python::exception() << '\n';
	}

	system("pause");

	return EXIT_SUCCESS;
}