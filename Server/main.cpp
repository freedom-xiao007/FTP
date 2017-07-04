#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

#include "Server.h"

//���̺߳����������Ķ��߳����д˺���
void server(SOCKET s);

void main()
{
	//������ص�����
	int iPort = 5050;//������˿�
	WSADATA wsaData;//Winsock ����������
	SOCKET sListen, sAccept;//�׽ӿڹؼ���,�ֱ����ڼ����ͽ�������
	int iLen;
	int iSend;
	char buf[] = "I am a server";
	struct sockaddr_in ser, cli;//�����ַ
	//������߳�ָ�룬���ڴ����߳�
	std::thread* t;
	//�����̵߳Ĺ������洴���Ķ��߳�ָ�룬�������ʱ�ͷ�ռ�õ��ڴ�
	std::vector<std::thread*> tManage;
	Server* server = NULL;


	std::cout << "----------------------------\n";
	std::cout << "Server waitting\n";
	std::cout << "----------------------------\n";

	//����winSocket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed to load Winsock.\n";
		return;
	}

	//����Socket
	sListen = socket(AF_INET, SOCK_STREAM, 0);
	if (sListen == INVALID_SOCKET) {
		std::cout << "socket() Failed:" << WSAGetLastError() <<"\n";
		return;
	}

	//��IP��ַ
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sListen, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR) {
		std::cout << "bind() Failed\n";
		return;
	}

	//����
	if (listen(sListen, 5) == SOCKET_ERROR) {
		std::cout << "listen() Failed\n";
		return;
	}

	iLen = sizeof(cli);//��ȡ�ͻ��������ַ�ĳ���

	//�������Ӻͷ��ͻ�ӭ��Ϣ
	//��ѭ��ʹ����һֱ����
	while (true) {
		//��������
		sAccept = accept(sListen, (struct sockaddr*)&cli, &iLen);
		if (sAccept == INVALID_SOCKET) {
			std::cout << "accept() Failed\n";
			break;
		}

		//�����µ��̣߳������������У������̺߳�̨����
		//t = new std::thread(server, sAccept);
		//tManage.push_back(t);
		//t->detach();
		server = new Server(sAccept);
		t = new std::thread(&Server::running, server);
		tManage.push_back(t);
		t->detach();
	}

	//�ͷ�ָ��ռ�õ��ڴ�
	for (int i = 0; i < tManage.size(); i++) {
		delete(tManage[i]);
	}

	//�رռ���
	closesocket(sListen);
	//�ر� Winsock
	WSACleanup();
}

//���̺߳����������Ķ��߳����д˺���
void server(SOCKET s) {
	SOCKET socket = s;
	struct sockaddr_in ser, cli;//�����ַ
	int iSend, iRecv;
	char buf[1024] = "I am a server";

	//��ʾ�ͻ��˵� IP ��Ϣ
	char clibuf[20] = { '\0' };
	inet_ntop(AF_INET, (void*)&cli.sin_addr, clibuf, 16);
	std::cout << "Accept client IP:" << clibuf << ":" << ntohs(cli.sin_port) << std::endl;

	//������Ϣ���ͻ���
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

	//ʹ��ѭ�����Ͻ��ܿͻ��˷���������Ϣ����ʾ
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