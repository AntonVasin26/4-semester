#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

class chat_TCP
{
public:
	chat_TCP(const std::string& user_name, boost::asio::ip::tcp::socket& socket) : m_user_name(user_name), m_exit_flag(false), g_socket(socket){}

	void run()
	{
		auto reader = std::thread(&chat_TCP::read, this);

		write();

		reader.join();
	}

	void read()
	{
		boost::asio::socket_base::bytes_readable command(true);
		g_socket.io_control(command);

		while (!m_exit_flag)
		{
			g_socket.io_control(command);
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

		boost::asio::read_until(g_socket, buffer, '#');

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
		boost::asio::write(g_socket, boost::asio::buffer(m_user_name + ":" + message + '#'));
	}


public:
	std::string m_user_name;
	bool m_exit_flag;
	boost::asio::ip::tcp::socket& g_socket;

};

void connect_to_server(const std::string& name, const std::string& ip, int port)
{
	try
	{
		boost::asio::ip::tcp::endpoint endpoint(
			boost::asio::ip::address::from_string(ip), port);

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());

		socket.connect(endpoint);

		chat_TCP chat(name, socket);

		std::string data = "systeam message: " + name + " connected to the server#";

		boost::asio::write(socket, boost::asio::buffer(data));

		chat.run();

		socket.close();
	}
	catch (boost::system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

		//return e.code().value();
	}

	system("pause");
}

void run_server(const std::string& name, int port)
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

		chat_TCP chat(name, socket);

		std::string data = "systeam message: Connecting to server succesesed#";

		boost::asio::write(socket, boost::asio::buffer(data));

		chat.run();

		socket.close();

	}
	catch (boost::system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

		//return e.code().value();
	}
}


int main()
{
	system("chcp 1251");
	run_server("Server", 3333);
	run_server("Server", 10000);
}
