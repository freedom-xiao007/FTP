#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
char* GetLocalAddress();
void main()
{
	//定义相关的数据
	int iPort = 5050;
	WSADATA wsaData;
	SOCKET sListen, sAccept;
	int iLen;
	int iSend;
	char buf[] = "I am a server";
	struct sockaddr_in ser, cli;

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

	//显示服务端地址
	struct sockaddr FAR* name = NULL;
	int FAR* len = NULL;
	if (getsockname(sListen, name, len) == 0) {
		char clibuf[20] = { '\0' };
		inet_ntop(AF_INET, (void*)&ser.sin_addr.s_addr, clibuf, 16);
		std::cout << "SERVER IP:" << clibuf << ":" << ntohs(ser.sin_port) << std::endl;
	}
	else {
		std::cout << "Get the server IP failed.\n";
		char clibuf[20] = { '\0' };
		inet_ntop(AF_INET, (void*)&ser.sin_addr.s_addr, clibuf, 16);
		std::cout << "SERVER IP:" << clibuf << ":" << ntohs(ser.sin_port) << std::endl;
		std::cout << GetLocalAddress();
	}

	//监听
	if (listen(sListen, 5) == SOCKET_ERROR) {
		std::cout << "listen() Failed\n";
		return;
	}

	//接受连接和发送欢迎信息
	iLen = sizeof(cli);
	while (true) {
		sAccept = accept(sListen, (struct sockaddr*)&cli, &iLen);
		if (sAccept == INVALID_SOCKET) {
			std::cout << "accept() Failed\n";
			break;
		}

		char clibuf[20] = { '\0' };
		inet_ntop(AF_INET, (void*)&cli.sin_addr, clibuf, 16);
		std::cout << "Accept client IP:" << clibuf << ":" << ntohs(cli.sin_port) << std::endl;

		iSend = send(sAccept, buf, sizeof(buf), 0);
		if (iSend == SOCKET_ERROR) {
			std::cout << "send() Failed\n";
			break;
		}
		else if (iSend == 0) {
			break;
		}
		else {
			std::cout << "Send byte:" << iSend << std::endl;
			std::cout << "----------------------------------\n";
		}
		closesocket(sAccept);
	}
	closesocket(sListen);
	WSACleanup();
}

//获取本地 IP 地址
char* GetLocalAddress()
{
	struct in_addr *pinAddr;
	LPHOSTENT	lpHostEnt;
	int			nRet;
	int			nLen;
	char        szLocalAddr[80];
	memset(szLocalAddr, 0, sizeof(szLocalAddr));
	// Get our local name
	nRet = gethostname(szLocalAddr, sizeof(szLocalAddr));
	if (nRet == SOCKET_ERROR)
	{
		return NULL;
	}
	// "Lookup" the local name
	lpHostEnt = gethostbyname(szLocalAddr);
	lpHostEnt = getaddrinfo(NULL, NULL, szLocalAddr, lpHostEnt);
	lpHostEnt = WSAAsyncGetHostByName(szLocalAddr);
	if (NULL == lpHostEnt)
	{
		return NULL;
	}
	// Format first address in the list
	pinAddr = ((LPIN_ADDR)lpHostEnt->h_addr);
	nLen = strlen(inet_ntoa(*pinAddr));
	if ((DWORD)nLen > sizeof(szLocalAddr))
	{
		WSASetLastError(WSAEINVAL);
		return NULL;
	}
	return inet_ntoa(*pinAddr);
}