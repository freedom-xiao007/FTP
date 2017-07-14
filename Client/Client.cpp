#include "Client.h"
#include "Tool.h"

#include <iostream>
#include <WS2tcpip.h>
#include <fstream>
#include <direct.h>

Client::Client()
{
	maxSize = 1024;
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
	//char addr[20] = "192.168.1.119";
	char addr[20] = "192.168.1.132";

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
		iLen = recv(client, buf, maxSize, 0);
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
			send(client, buf, 1024, 0);
			downloadFile(paramter);
			break;

		case 2:
			std::cout << "Start send file to server.\n";
			send(client, buf, 1024, 0);
			uploadFile(paramter);
			break;

		default:
			std::cout << "Command is invalid\n";
		}
	}
}

bool Client::uploadFile(std::string filePath)
{
	//���ļ�
	char* workPath = _getcwd(NULL, 0);
	if (workPath == NULL) {
		std::cout << "Get current work path failed\n";
	}
	else {
		std::cout << workPath << std::endl;
	}
	std::string absolutePath = workPath;
	absolutePath += "\\";
	absolutePath += filePath;
	std::ifstream file(absolutePath.c_str(), std::ios_base::binary);

	if (!file) {
		std::cout << "file open failed.\n";
		return false;
	}
	else {
		std::cout << "open successful\n";
	}

	//��ȡ�ļ���С
	long fileBegin = file.tellg();
	file.seekg(0, std::ios_base::end);
	long fileEnd = file.tellg();
	int fileSize = fileEnd - fileBegin;
	std::cout << "File size is " << fileEnd-fileBegin << " bytes" << std::endl;
	//���ļ���С���͸������
	_itoa_s(fileSize, buf, 10);
	send(client, buf, 1024, 0);

	//��ȡ�ļ�����
	std::cout << "��ʼ��ȡ�ļ�����" << std::endl;
	file.seekg(0, std::ios_base::beg);
	int sendCount = 0;
	while(!file.eof()) {
		memset(buf, 0, 1024);
		file.read(buf, 1024);

		int len = send(client, buf, maxSize, 0);
		if (len == SOCKET_ERROR) {
			std::cout << "Sending occur error\n";
		}

		sendCount += 1024;
		std::cout << "Send " << sendCount << "/" << fileSize << " bytes\n";
	}

	//�ر��ļ�
	file.close();
	std::cout << "Readed file succesful\n";

	return false;
}

bool Client::downloadFile(std::string file)
{
	return false;
}

int Client::commandParse(char * instruck, std::string & paramter)
{
	std::string string(buf);
	//std::cout << string;
	std::vector<std::string> command;
	Tool::splitString(string, command, std::string(" "));

	if (command.size() != 2) {
		paramter = "";
		return -1;
	}

	if (command[0] == "STOR") {
		paramter = command[1];
		return 2;
	}
	if (command[0] == "RETR") {
		paramter = command[1];
		return 1;
	}

	return 0;
}
