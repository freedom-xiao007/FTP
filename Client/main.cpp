#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
void main()
{
	//定义相应的数据
	WSADATA wsaData;
	SOCKET sClient;
	int iPort = 5050;
	int iLen;
	char buf[1024];
	struct sockaddr_in ser;

	//启动 winSocket
	memset(buf, 0, sizeof(buf));
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed to load Winsock\n";
		system("pause");
		return;
	}

	//创建Socket
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	char addr[20] = { '\0' };
	std::cin >> addr;
	inet_pton(AF_INET, addr, (void*)&ser.sin_addr.s_addr);
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sClient == INVALID_SOCKET) {
		std::cout << "socket() Failed\n";
		system("pause");
		return;
	}

	//连接并进行简单的操作
	if (connect(sClient, (struct sockaddr*)&ser, sizeof(ser)) == INVALID_SOCKET) {
		std::cout << "connect() Failed\n";
		system("pause");
		return;
	}
	else {
		iLen = recv(sClient, buf, sizeof(buf), 0);
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

	closesocket(sClient);
	WSACleanup();
	
	system("pause");
}
