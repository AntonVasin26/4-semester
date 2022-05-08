#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

class chat_TCP
{
public:
	std::string m_user_name;
	bool m_exit_flag;
	std::shared_ptr< boost::asio::ip::tcp::socket> m_socket_ptr;

public:
	chat_TCP(const std::string& user_name) : m_user_name(user_name), m_exit_flag(false), m_socket_ptr(nullptr) {}

	void connect_to_server(const std::string& ip, int port)
	{
		try
		{
			boost::asio::ip::tcp::endpoint endpoint(
				boost::asio::ip::address::from_string(ip), port);

			boost::asio::io_service io_service;

			m_socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(io_service, endpoint.protocol());

			(*m_socket_ptr).connect(endpoint);

			std::string data = "systeam message: " + m_user_name + " connected to the server#";

			send_message(data);

			run();

			(*m_socket_ptr).close();
		}
		catch (boost::system::system_error& e)
		{
			std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

			//return e.code().value();
		}

		system("pause");
	}

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

			m_socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(io_service);

			acceptor.accept(*m_socket_ptr);

			std::string data = "systeam message: Connecting to server succesesed#";

			send_message(data);

			run();

			(*m_socket_ptr).close();

		}
		catch (boost::system::system_error& e)
		{
			std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

			//return e.code().value();
		}
	}

	void run()
	{
		auto reader = std::thread(&chat_TCP::read, this);

		write();

		reader.join();
	}

	void read()
	{
		boost::asio::socket_base::bytes_readable command(true);
		(*m_socket_ptr).io_control(command);

		while (!m_exit_flag)
		{
			(*m_socket_ptr).io_control(command);
			if (command.get() > 0)
			{
				std::cout << read_message() << std::endl;
			}
		}
	}

	void write()
	{
		std::string message;
		while (!m_exit_flag)
		{
			std::string message;
			std::getline(std::cin, message);
			if (m_exit_flag)
				break;
			send_message(message);
		}
	}

	std::string read_message()
	{
		boost::asio::streambuf buffer;

		boost::asio::read_until(*m_socket_ptr, buffer, '#');

		std::string message;

		// Because buffer 'buf' may contain some other data
		// after '\n' symbol, we have to parse the buffer and
		// extract only symbols before the delimiter.
		std::istream input_stream(&buffer);
		std::getline(input_stream, message, '#');

		if (message.find(":disconect") != std::string::npos)
		{
			m_exit_flag = true;
			return "system message: " + message;
		}

		return message;
	}

	void send_message(const std::string& message)
	{
		if (message == ":disconect")
			m_exit_flag = true;
		boost::asio::write(*m_socket_ptr, boost::asio::buffer(m_user_name + ":" + message + '#'));
	}

};

int main()
{
	system("chcp 1251");
	chat_TCP chat("Server");
	chat.connect_to_server("127.0.0.1", 3333);
	//chat.connect_to_server("93.175.8.9", 10000);
}

//this is what the server looks like
//int main()
//{
//	system("chcp 1251");
//	chat_TCP chat("Server");
//	chat.run_server(3333);
//	//chat.run_server("10000);
//}