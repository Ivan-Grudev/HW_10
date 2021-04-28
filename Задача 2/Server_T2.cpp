#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;

char name[50];

std::string read_data_until(boost::asio::ip::tcp::socket & socket)
{
	boost::asio::streambuf buffer;

	boost::asio::read_until(socket, buffer, '!');
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;

char name[50];

std::string read_data_until(boost::asio::ip::tcp::socket & socket)
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

void write_data(boost::asio::ip::tcp::socket& socket)
{
	char message[50];
	std::cout << "Write your message: ";
	std::cin.getline(message, 50);
	std::string data = name;
	data += ": ";
	data += message;
	data += "!EOF";
	boost::asio::write(socket, boost::asio::buffer(data));
}

int main(int argc, char ** argv)
{
	system("chcp 1251");

	const std::size_t size = 30;

	auto port = 8000;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

	boost::asio::io_service io_service;

	try
	{
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

		acceptor.bind(endpoint);

		acceptor.listen(size);

		boost::asio::ip::tcp::socket socket(io_service);

		acceptor.accept(socket);

		std::cout << "connection succeed" << std::endl;
		std::cout << "Write your name: ";
		std::cin.getline(name, 50);

		while (true) {
			std::cout << read_data_until(socket) << std::endl;
			write_data(socket);
		}
	}
	catch (boost::system::system_error & e)
	{
		std::cout << "Chat is ended. " << e.what() << std::endl;

		system("pause");

		return e.code().value();
	}

	system("pause");

	return EXIT_SUCCESS;
}
	std::string message;

	// Because buffer 'buf' may contain some other data
	// after '\n' symbol, we have to parse the buffer and
	// extract only symbols before the delimiter.
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '!');

	return message;
}

void write_data(boost::asio::ip::tcp::socket& socket)
{
	char message[50];
	std::cout << "Write your message: ";
	std::cin.getline(message, 50);
	std::string data = name;
	data += ": ";
	data += message;
	data += "!EOF";
	boost::asio::write(socket, boost::asio::buffer(data));
}

int main(int argc, char ** argv)
{
	system("chcp 1251");

	const std::size_t size = 30;

	auto port = 8000;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

	boost::asio::io_service io_service;

	try
	{
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

		acceptor.bind(endpoint);

		acceptor.listen(size);

		boost::asio::ip::tcp::socket socket(io_service);

		acceptor.accept(socket);

		std::cout << "connection succeed" << std::endl;
		std::cout << "Write your name: ";
		std::cin.getline(name, 50);

		while (true) {
			std::cout << read_data_until(socket) << std::endl;
			write_data(socket);
		}
	}
	catch (boost::system::system_error & e)
	{
		std::cout << "Chat is ended. " << e.what() << std::endl;

		system("pause");

		return e.code().value();
	}

	system("pause");

	return EXIT_SUCCESS;
}

