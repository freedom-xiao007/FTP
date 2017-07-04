#include "Server.h"
#include "Tool.h"

#include <iostream>
#include <vector>

Server::Server(SOCKET s)
	:server(s)
{
	maxLen = 1024;
}


Server::~Server()
{
}

bool Server::welcome()
{
	char welcome[1024] = "Welcome, my friend\n";

	//发送信息给客户端
	int iSend = send(server, welcome, sizeof(welcome), 0);
	if (iSend == SOCKET_ERROR) {
		std::cout << "send() Failed\n";
		return false;
	}

	return true;
}

void Server::running()
{
	welcome();

	while (true) {
		if (recv(server, buf, maxLen, 0) == 0) {
			std::cout << "recv() Faied!\n";
		}

		std::string paramter;
		int cmd = commandParse(buf, paramter);

		switch (cmd) {
		case 0:
			std::cout << "Command is invalid\n";
			break;

		case 1:
			std::cout << "Start receive the file from client.\n";
			receiveFile(paramter);
			break;

		case 2:
			std::cout << "Start send file to client.\n";
			sendFile(paramter);
			break;

		default:
			std::cout << "Command is invalid\n";
		}
	}
}

int Server::commandParse(char* instruck, std::string &paramter)
{
	std::string string(buf);
	std::cout << string;
	std::vector<std::string> command;
	Tool::splitString(string, command, std::string(" "));
	//std::cout << command[0] << " " << command[1] << std::endl;

	if (command.size() != 2) {
		paramter = "";
		return -1;
	}

	if (command[0] == "STOR") {
		paramter = command[1];
		return 1;
	}
	if (command[0] == "RETR") {
		paramter = command[1];
		return 2;
	}

	return -1;
}

bool Server::receiveFile(std::string filename)
{
	return false;
}

bool Server::sendFile(std::string filename)
{
	return false;
}
