#include <iostream>
#include <vector>
#include "client.h"

Socket_sender::Socket_sender()
{
	server_ip = "127.0.0.2";
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "Error while creating socket\n";
		exit (1);
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	if (inet_pton(AF_INET, server_ip.c_str() , &server_addr.sin_addr) <= 0)	{
		std::cerr << "inet_pton error\n";
		exit(1);
	}
	if (connect(sockfd, (SA *) &server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "connect failed\n";
		exit(1);
	}
}

void Socket_sender::send_and_recv(const std::string& send_line)
{
	int n = 0;
	this->send_line = send_line;
	if (send(sockfd, send_line.c_str(), send_line.size(), 0) != send_line.size()) {
		std::cerr << "write error\n";
		exit(1);
	}
	char ch;
	while ((n = recv(sockfd, &ch, 1, 0))) {
		if (ch == '\r') { break; }
		std::cout << ch;
	}
	if (n < 0) {
		std::cerr << "read error\n";
		exit(1);
	}
}

Socket_sender::~Socket_sender() {}

int main()
{
	std::string str;
	Socket_sender socket;
	std::cout << "redis -> ";
	while (std::getline(std::cin, str))
	{
		socket.send_and_recv(str);
		std::cout << std::endl;
		if ("EXIT" == str) { break; }
		std::cout<< "redis -> ";
	}
	return 0;
}

