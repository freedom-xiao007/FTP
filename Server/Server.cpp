#include "Server.h"
#include "Tool.h"

#include <iostream>
#include <fstream>
#include <vector>

Server::Server(SOCKET s)
	:server(s)
{
	maxSize = 1024;
	storePath = ".\\temp\\";
	//buf = new char[maxSize];
}


Server::~Server()
{
}

bool Server::welcome()
{
	char *welcome = "Welcome, my friend\n";

	//发送信息给客户端
	int iSend = send(server, welcome, 1024, 0);
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
		if (recv(server, buf, maxSize, 0) == 0) {
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
	std::cout << string << std::endl;
	std::vector<std::string> command;
	Tool::splitString(string, command, std::string(" "));

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
	//创建与上次文件名相同的文件
	std::string filePath = storePath + filename;
	std::ofstream storeFile(filePath, std::ios_base::binary);
	if (!storeFile) {
		std::cout << "Create file failed\n";
	}

	//先接收文件大小信息
	memset(buf, 0, maxSize);
	recv(server, buf, 1024, 0);
	int fileSize = atoi(buf);
	std::cout << "File's size is:" << fileSize << std::endl;

	int len = 1;
	int recvCount = 0;
	//统计文件传输剩下的大小
	int remain = fileSize;
	while (true) {
		memset(buf, 0, maxSize);
		len = recv(server, buf, 1024, 0);
		storeFile.write(buf, 1024);
		if (len == SOCKET_ERROR) {
			std::cout << "Receive occur error\n";
		}

		//如果剩下的小于等于0，说明文件传输完毕，退出循环
		remain -= 1024;
		if(remain <= 0) {
		//if (strlen(buf) == 0) {
			break;
		}

		recvCount += strlen(buf);
		std::cout << "Receive " << recvCount << " bytes\n";
	}

	//关闭并保存文件
	storeFile.close();
	std::cout << "Write file successful\n";

	return false;
}

bool Server::sendFile(std::string filename)
{
	return false;
}
