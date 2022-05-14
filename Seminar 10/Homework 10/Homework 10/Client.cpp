#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

class chat_TCP
{
	using socket = boost::asio::ip::tcp::socket;
private:
	static inline const std::size_t max_connections = 30;

	boost::asio::io_service io_service;
	std::string m_user_name;
	boost::asio::ip::tcp::endpoint endpoint;
	boost::asio::ip::tcp::acceptor acceptor;
	bool m_exit_flag;
	std::shared_ptr<socket> m_socket_ptr;


public:
	chat_TCP(const std::string& user_name) : 
		m_user_name(user_name), m_exit_flag(false), m_socket_ptr(nullptr), acceptor(io_service)
	{}

	void connect_to_server(const std::string& ip, int port)
	{
		try
		{
			endpoint.address(boost::asio::ip::address::from_string(ip));
			endpoint.port(port);

			m_socket_ptr = std::make_shared<socket>(io_service, endpoint.protocol());

			(*m_socket_ptr).connect(endpoint);

			std::string data = "systeam message: " + m_user_name + " connected to the server#";

			send_message(data);

			run();

			(*m_socket_ptr).close();
		}
		catch (const boost::system::system_error& e)
		{
			std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

			//return e.code().value();
		}

		system("pause");
	}

	void run_server(int port)
	{
		endpoint.address(boost::asio::ip::address_v4::any());
		endpoint.port(port);

		try
		{
			acceptor.open(endpoint.protocol());
			acceptor.bind(endpoint);
			acceptor.listen(max_connections);

			m_socket_ptr = std::make_shared<socket>(io_service);

			acceptor.accept(*m_socket_ptr);

			std::string data = "systeam message: Connecting to server succesesed#";

			send_message(data);

			run();

			(*m_socket_ptr).close();

		}
		catch (const boost::system::system_error& e)
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
	chat_TCP chat("Anton");
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