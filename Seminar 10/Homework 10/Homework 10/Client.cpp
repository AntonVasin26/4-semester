#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

class Chat1
{
public:
	Chat1(const std::string& user_name) : m_user_name(user_name), m_exit_flag(false) {}

	void run_server(int port)
	{
		const std::size_t size = 30;

		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

		boost::asio::io_service io_service;

		try
		{
			boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

			acceptor.bind(endpoint);

			acceptor.listen(size);

			boost::asio::ip::tcp::socket socket(io_service);

			acceptor.accept(socket);

			std::string data = "Connecting to server accesesed";

			boost::asio::write(socket, boost::asio::buffer(data));

			run(socket);

		}
		catch (boost::system::system_error& e)
		{
			std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

			//return e.code().value();
		}
	}

	void run(boost::asio::ip::tcp::socket& socket)
	{
		auto reader = std::thread(&Chat1::read, socket);

		write();

		reader.join();

		send_message(" left the chat");
	}

	void read(boost::asio::ip::tcp::socket& socket)
	{
		send_message(" joined the chat");

		while (true)
		{
			if (m_exit_flag)
			{
				break;
			}

			if
			boost::asio::streambuf buffer;
			boost::asio::read_until(socket, buffer, '\n');

			std::string message;

			// Because buffer 'buf' may contain some other data
			// after '\n' symbol, we have to parse the buffer and
			// extract only symbols before the delimiter.
			std::istream input_stream(&buffer);
			std::getline(input_stream, message, '\n');
			std::cout << message;
		}
	}

	void write()
	{

	}

	void send_message(std::string message)
	{

	}


private:
	std::string m_user_name;
	bool m_exit_flag;

};


int main()
{
	system("chcp 1251");



}