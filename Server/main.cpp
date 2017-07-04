#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

#include "Server.h"

//多线程函数，创建的多线程运行此函数
void server(SOCKET s);

void main()
{
	//定义相关的数据
	int iPort = 5050;//定义其端口
	WSADATA wsaData;//Winsock 的启动参数
	SOCKET sListen, sAccept;//套接口关键字,分别用于监听和接收连接
	int iLen;
	int iSend;
	char buf[] = "I am a server";
	struct sockaddr_in ser, cli;//网络地址
	//定义多线程指针，用于创建线程
	std::thread* t;
	//用于线程的管理，保存创建的多线程指针，程序结束时释放占用的内存
	std::vector<std::thread*> tManage;
	Server* server = NULL;


	std::cout << "----------------------------\n";
	std::cout << "Server waitting\n";
	std::cout << "----------------------------\n";

	//启动winSocket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed to load Winsock.\n";
		return;
	}

	//创建Socket
	sListen = socket(AF_INET, SOCK_STREAM, 0);
	if (sListen == INVALID_SOCKET) {
		std::cout << "socket() Failed:" << WSAGetLastError() <<"\n";
		return;
	}

	//绑定IP地址
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sListen, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR) {
		std::cout << "bind() Failed\n";
		return;
	}

	//监听
	if (listen(sListen, 5) == SOCKET_ERROR) {
		std::cout << "listen() Failed\n";
		return;
	}

	iLen = sizeof(cli);//获取客户端网络地址的长度

	//接受连接和发送欢迎信息
	//用循环使程序一直运行
	while (true) {
		//接收连接
		sAccept = accept(sListen, (struct sockaddr*)&cli, &iLen);
		if (sAccept == INVALID_SOCKET) {
			std::cout << "accept() Failed\n";
			break;
		}

		//创建新的线程，并加入容器中，并将线程后台运行
		//t = new std::thread(server, sAccept);
		//tManage.push_back(t);
		//t->detach();
		server = new Server(sAccept);
		t = new std::thread(&Server::running, server);
		tManage.push_back(t);
		t->detach();
	}

	//释放指针占用的内存
	for (int i = 0; i < tManage.size(); i++) {
		delete(tManage[i]);
	}

	//关闭监听
	closesocket(sListen);
	//关闭 Winsock
	WSACleanup();
}

//多线程函数，创建的多线程运行此函数
void server(SOCKET s) {
	SOCKET socket = s;
	struct sockaddr_in ser, cli;//网络地址
	int iSend, iRecv;
	char buf[1024] = "I am a server";

	//显示客户端的 IP 信息
	char clibuf[20] = { '\0' };
	inet_ntop(AF_INET, (void*)&cli.sin_addr, clibuf, 16);
	std::cout << "Accept client IP:" << clibuf << ":" << ntohs(cli.sin_port) << std::endl;

	//发送信息给客户端
	iSend = send(socket, buf, sizeof(buf), 0);
	if (iSend == SOCKET_ERROR) {
		std::cout << "send() Failed\n";
	}
	else if (iSend == 0) {
		std::cout << "send() Zero\n";
	}
	else {
		std::cout << "Send byte:" << iSend << std::endl;
		std::cout << "----------------------------------\n";
	}

	//使用循环不断接受客户端发送来的信息并显示
	while (true) {
		iRecv = recv(socket, buf, sizeof(buf), 0);
		if (iRecv == 0) {
			//std::cout << "recv() Zero\n";
		}
		else if (iRecv == SOCKET_ERROR) {
			std::cout << "recv() Failed\n";
		}
		else {
			std::cout << "recv() data from server:" << buf << std::endl;
		}
	}
}