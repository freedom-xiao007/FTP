#include "Client.h"
#include "Tool.h"

#include <iostream>
#include <WS2tcpip.h>

Client::Client()
{
}


Client::~Client()
{
	//�ر����Ӳ��˳�
	closesocket(client);
	//�ر� Winsock
	WSACleanup();
}

void Client::running()
{
	memset(buf, 0, sizeof(buf));
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed to load Winsock\n";
		system("pause");
		return;
	}

	//char addr[20] = "113.54.167.16";
	char addr[20] = "192.168.1.119";

	//����Socket
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	inet_pton(AF_INET, addr, (void*)&ser.sin_addr.s_addr);
	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client == INVALID_SOCKET) {
		std::cout << "socket() Failed\n";
		system("pause");
		return;
	}

	//���Ӳ����м򵥵Ĳ���
	if (connect(client, (struct sockaddr*)&ser, sizeof(ser)) == INVALID_SOCKET) {
		std::cout << "connect() Failed\n";
		system("pause");
		return;
	}
	else {
		//���շ���˷��͵�����
		iLen = recv(client, buf, sizeof(buf), 0);
		if (iLen == 0) {
			system("pause");
			return;
		}
		else if (iLen == SOCKET_ERROR) {
			std::cout << "recv() Failed\n";
			system("pause");
			return;
		}
		std::cout << "recv() data from server:" << buf << std::endl;
	}

	while (true) {
		//������Ӧ�����ݷ��͸������
		std::cout << ">>";
		std::cin.getline(buf, 1024);

		std::string paramter;
		int cmd = commandParse(buf, paramter);

		switch (cmd) {
		case 0:
			std::cout << "Command is invalid\n";
			break;

		case 1:
			std::cout << "Start receive the file from client.\n";
			downloadFile(paramter);
			break;

		case 2:
			std::cout << "Start send file to client.\n";
			uploadFile(paramter);
			break;

		default:
			std::cout << "Command is invalid\n";
		}
	}
}

bool Client::connectServer(const sockaddr_in &addr)
{
	//���Ӳ����м򵥵Ĳ���
	if (connect(client, (struct sockaddr*)&addr, sizeof(addr)) == INVALID_SOCKET) {
		std::cout << "connect() Failed\n";
		system("pause");
		return false;
	}
	else {
		//���շ���˷��͵�����
		int iLen = recv(client, buf, sizeof(buf), 0);
		if (iLen == 0) {
			std::cout << "recv() zero\n";
			system("pause");
			return false;
		}
		else if (iLen == SOCKET_ERROR) {
			std::cout << "recv() Failed\n";
			system("pause");
			return false;
		}
		std::cout << "recv() data from server:" << buf << std::endl;
	}

	return true;
}

bool Client::uploadFile(std::string file)
{
	return false;
}

bool Client::downloadFile(std::string file)
{
	return false;
}

int Client::commandParse(char * instruck, std::string & paramter)
{
	std::string string(buf);
	std::cout << string;
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

	return 0;
}
