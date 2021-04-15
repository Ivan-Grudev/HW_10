#include <iostream>
#include <string>

#include <boost/asio.hpp>

void write_data(boost::asio::ip::tcp::socket& socket)
{
	std::string name;
	//char name[] = "";
	std::cout << "Write your name: ";
	std::cin >> name;
	std::string message;
	//char message[] = "";
	std::cout << "Write your message: ";
	std::cin >> message;
//	std::string data = "Hello, Network Programming!EOF";
//	std::string data = name + ": " + message + "!EOF";
	//std::string data = name + ": " + message;
	std::string data = name + ": " + message + "!EOF";
	//char data[] = "";
	//strcat(data, name);
	//strcat(data, ": ");
	//message = message + "!EOF";
	//strcat(message, "!EOF");
	//strcat(data, message);
	//std::string data = message + "!EOF";
	std::cout << std::endl << data << std::endl;
	//std::string data = message;

	boost::asio::write(socket, boost::asio::buffer(data));
}

std::string read_data(boost::asio::ip::tcp::socket& socket)
{
	const std::size_t length = 10;
	char buffer[length];
	boost::asio::read(socket, boost::asio::buffer(buffer, length));
	return std::string(buffer, length);
}

std::string read_data_until(boost::asio::ip::tcp::socket& socket)
{
	boost::asio::streambuf buffer;

	boost::asio::read_until(socket, buffer, '!');

	std::string message;

	// Because buffer 'buf' may contain some other data
	// after '\n' symbol, we have to parse the buffer and
	// extract only symbols before the delimiter.
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '!');

	return message;
}

int main(int argc, char** argv)
{
	system("chcp 1251");

	std::string raw_ip_address = "127.0.0.1";

	auto port = 3333;

	try
	{
		boost::asio::ip::tcp::endpoint endpoint(
		boost::asio::ip::address::from_string(raw_ip_address), port);

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());

		socket.connect(endpoint);

		write_data(socket);
	}
	catch (boost::system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

		system("pause");

		return e.code().value();
	}

	system("pause");

	return EXIT_SUCCESS;
}
