#include <iostream>
#include <string>

#include <boost/asio.hpp>

char name[50];

void write_data(boost::asio::ip::tcp::socket& socket)
{
	char message[50];
	std::cout << "Write your message: ";
	std::cin.getline(message, 50);
	std::string data = name;
	data += ": ";
	data += message;
	data += "!EOF";
	std::cout << std::endl << data << std::endl;

	boost::asio::write(socket, boost::asio::buffer(data));
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

		std::cout << "Write your name: ";
		std::cin.getline(name, 50);
		while(true) 
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
