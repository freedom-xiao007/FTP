#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

#include "Client.h"

void main()
{
	//������Ӧ������
	//WSADATA wsaData;
	//SOCKET sClient;
	//int iPort = 5050;//��Ӧ�ķ���˵Ķ˿�
	//int iLen, iSend;
	//char buf[1024];
	//struct sockaddr_in ser;

	//���� winSocket
	//memset(buf, 0, sizeof(buf));
	//if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
	//	std::cout << "Failed to load Winsock\n";
	//	system("pause");
	//	return;
	//}

	//char addr[20] = { '\0' };
	//std::cin >> addr;//�������� IP ��ַ
	//char addr[20] = "192.168.1.119";
	//char addr[20] = "113.54.167.16";

	//����Socket
	//ser.sin_family = AF_INET;
	//ser.sin_port = htons(iPort);
	//inet_pton(AF_INET, addr, (void*)&ser.sin_addr.s_addr);
	//sClient = socket(AF_INET, SOCK_STREAM, 0);
	//if (sClient == INVALID_SOCKET) {
	//	std::cout << "socket() Failed\n";
	//	system("pause");
	//	return;
	//}

	////���Ӳ����м򵥵Ĳ���
	//if (connect(sClient, (struct sockaddr*)&ser, sizeof(ser)) == INVALID_SOCKET) {
	//	std::cout << "connect() Failed\n";
	//	system("pause");
	//	return;
	//}
	//else {
	//	//���շ���˷��͵�����
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

	////�Է���˷���ָ���������
	//int index = 0;//�������ϵ�����Ȼ���͸�����ˣ�������֤���߳��Ƿ�����
	//char* command, paramter;
	//while (true) {
	//	//������Ӧ�����ݷ��͸������
	//	std::cout << ">>";
	//	std::cin.getline(buf, 1024);
	//	std::cout << std::endl <<  buf;

	//	//������ת��Ϊ�ַ���
	//	//_itoa_s(index, buf, 10);
	//	//++index;

	//	//�������ݵ������
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

	//�ر����Ӳ��˳�
	//closesocket(sClient);
	//�ر� Winsock
	//WSACleanup();
	
	Client client;
	client.running();
	system("pause");
}
