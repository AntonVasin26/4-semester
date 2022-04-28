#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

class chat_TCP
{
public:
	chat_TCP(const std::string& user_name) : m_user_name(user_name), m_exit_flag(false) {}


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

			std::string data = "systeam message: Connecting to server succesesed#";

			boost::asio::write(socket, boost::asio::buffer(data));

			run(socket);

		}
		catch (boost::system::system_error& e)
		{
			std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

			//return e.code().value();
		}
	}
	
	void connect_to_server(const std::string& ip, int port)
	{
		try
		{
			boost::asio::ip::tcp::endpoint endpoint(
				boost::asio::ip::address::from_string(ip), port);

			boost::asio::io_service io_service;

			boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());

			socket.connect(endpoint);

			std::string data = "systeam message: " + m_user_name + " connected to the server#";

			boost::asio::write(socket, boost::asio::buffer(data));

			run(socket);
		}
		catch (boost::system::system_error& e)
		{
			std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

			//return e.code().value();
		}

		system("pause");
	}

	void run(boost::asio::ip::tcp::socket& socket)
	{
		auto reader = std::thread(this, &chat_TCP::read, socket);

		write(socket);

		reader.join();

		send_message(socket, "left the chat");
	}

	void read(boost::asio::ip::tcp::socket& socket)
	{
		boost::asio::socket_base::bytes_readable command(true);
		socket.io_control(command);

		while (true)
		{
			if (m_exit_flag)
			{
				break;
			}

			socket.io_control(command);
			if (command.get() > 0)
			{
				std::cout << read_message(socket) << std::endl;
			}
		}
	}

	void write(boost::asio::ip::tcp::socket& socket)
	{
		std::string message;
		while (true)
		{
			if (m_exit_flag)
			{
				break;
			}

			std::string message;
			std::getline(std::cin, message);
			send_message(socket, message);
		}
	}

	std::string read_message(boost::asio::ip::tcp::socket& socket)
	{
		boost::asio::streambuf buffer;

		boost::asio::read_until(socket, buffer, '#');

		std::string message;

		// Because buffer 'buf' may contain some other data
		// after '\n' symbol, we have to parse the buffer and
		// extract only symbols before the delimiter.
		std::istream input_stream(&buffer);
		std::getline(input_stream, message, '#');

		if (message.find("//exit") != std::string::npos)
		{
			m_exit_flag = true;
			message.erase(*std::end(message) - 7, 7);
			return "system message: " + message + "left the chat";
		}

		return message;
	}

	void send_message(boost::asio::ip::tcp::socket& socket, const std::string& message)
	{
		if (message == "//exit")
			m_exit_flag = true;
		boost::asio::write(socket, boost::asio::buffer(m_user_name + ": " + message + '#'));
	}


private:
	std::string m_user_name;
	bool m_exit_flag;
};


int main()
{
	system("chcp 1251");
	chat_TCP client("Anton");
	client.connect_to_server("127.0.0.1", 3333);
}