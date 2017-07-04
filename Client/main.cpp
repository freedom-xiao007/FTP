#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

#include "Client.h"

void main()
{
	//定义相应的数据
	//WSADATA wsaData;
	//SOCKET sClient;
	//int iPort = 5050;//对应的服务端的端口
	//int iLen, iSend;
	//char buf[1024];
	//struct sockaddr_in ser;

	//启动 winSocket
	//memset(buf, 0, sizeof(buf));
	//if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
	//	std::cout << "Failed to load Winsock\n";
	//	system("pause");
	//	return;
	//}

	//char addr[20] = { '\0' };
	//std::cin >> addr;//输入服务端 IP 地址
	//char addr[20] = "192.168.1.119";
	//char addr[20] = "113.54.167.16";

	//创建Socket
	//ser.sin_family = AF_INET;
	//ser.sin_port = htons(iPort);
	//inet_pton(AF_INET, addr, (void*)&ser.sin_addr.s_addr);
	//sClient = socket(AF_INET, SOCK_STREAM, 0);
	//if (sClient == INVALID_SOCKET) {
	//	std::cout << "socket() Failed\n";
	//	system("pause");
	//	return;
	//}

	////连接并进行简单的操作
	//if (connect(sClient, (struct sockaddr*)&ser, sizeof(ser)) == INVALID_SOCKET) {
	//	std::cout << "connect() Failed\n";
	//	system("pause");
	//	return;
	//}
	//else {
	//	//接收服务端发送的数据
	//	iLen = recv(sClient, buf, sizeof(buf), 0);
	//	if (iLen == 0) {
	//		system("pause");
	//		return;
	//	}
	//	else if (iLen == SOCKET_ERROR) {
	//		std::cout << "recv() Failed\n";
	//		system("pause");
	//		return;
	//	}
	//	std::cout << "recv() data from server:" << buf << std::endl;
	//}

	////对服务端发送指令或者数据
	//int index = 0;//此数不断递增，然后发送给服务端，用于验证多线程是否有用
	//char* command, paramter;
	//while (true) {
	//	//输入相应的数据发送给服务端
	//	std::cout << ">>";
	//	std::cin.getline(buf, 1024);
	//	std::cout << std::endl <<  buf;

	//	//将数字转换为字符串
	//	//_itoa_s(index, buf, 10);
	//	//++index;

	//	//发送数据到服务端
	//	iSend = send(sClient, buf, sizeof(buf), 0);
	//	if (iSend == SOCKET_ERROR) {
	//		std::cout << "send() Failed\n";
	//	}
	//	else if (iSend == 0) {
	//		std::cout << "send() Zero\n";
	//	}
	//	else {
	//		std::cout << "Send byte:" << iSend << std::endl;
	//		std::cout << "----------------------------------\n";
	//	}
	//}

	//关闭连接并退出
	//closesocket(sClient);
	//关闭 Winsock
	//WSACleanup();
	
	Client client;
	client.running();
	system("pause");
}
