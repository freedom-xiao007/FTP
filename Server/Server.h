#pragma once

#include <Winsock2.h>
#include <string>

class Server
{
public:
	Server(SOCKET s);
	~Server();

	//��ӭ����
	bool welcome();
	//��������к���
	void running();
	//�����������
	int commandParse(char* instruck, std::string &paramter);
	//�ļ����պ���
	bool receiveFile(std::string filename);
	//�ļ�����
	bool sendFile(std::string filename);

private:
	SOCKET server;
	int maxLen;
	char buf[1024];
};

