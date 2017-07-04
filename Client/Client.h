#pragma once
#include <WinSock2.h>
#include <string>

class Client
{
public:
	Client();
	~Client();

	void running();
	bool connectServer(const sockaddr_in &addr);
	bool uploadFile(std::string file);
	bool downloadFile(std::string file);
	int commandParse(char* instruck, std::string &paramter);

private:
	SOCKET client;
	char buf[1024];
	//������Ӧ������
	WSADATA wsaData;
	int iPort = 5050;//��Ӧ�ķ���˵Ķ˿�
	int iLen, iSend;
	struct sockaddr_in ser;

};

