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
	//定义相应的数据
	WSADATA wsaData;
	int iPort = 5050;//对应的服务端的端口
	int iLen, iSend;
	struct sockaddr_in ser;

};

