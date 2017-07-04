#pragma once

#include <Winsock2.h>
#include <string>

class Server
{
public:
	Server(SOCKET s);
	~Server();

	//欢迎函数
	bool welcome();
	//服务端运行函数
	void running();
	//命令解析函数
	int commandParse(char* instruck, std::string &paramter);
	//文件接收函数
	bool receiveFile(std::string filename);
	//文件发送
	bool sendFile(std::string filename);

private:
	SOCKET server;
	int maxLen;
	char buf[1024];
};

