#include "../include/Connect.h"

void Connect::startServer()
{
	WSADATA wsaData;
	ADDRINFO hints;
	ADDRINFO* addrResult = NULL;
	SOCKET clientSocket = INVALID_SOCKET;
	SOCKET listenSocket = INVALID_SOCKET;
	char recvBuffer[512];
			
	CH.startQueueHandler();
	
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 1) {
		cout << "(!) WSAStartup error\n";
		WSACleanup();
	}
	else if (getaddrinfo(NULL, "5461", &hints, &addrResult) == 1) { // here is the IP address and the port on which the server will work
		cout << "(!) getaddrinfo error\n";
		WSACleanup();
		freeaddrinfo(addrResult);
	}
	else if ((listenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol)) == INVALID_SOCKET) {
		cout << "(!) socket error\n";
		WSACleanup();
		freeaddrinfo(addrResult);
		closesocket(listenSocket);
	}
	else if (bind(listenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen) == SOCKET_ERROR) {
		cout << "(!) bind error\n";
		WSACleanup();
		freeaddrinfo(addrResult);
		closesocket(listenSocket);
	}
	else if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "(!) listen error\n";
		WSACleanup();
		freeaddrinfo(addrResult);
		closesocket(listenSocket);
	}
	else {
		while (true) {
			if ((clientSocket = accept(listenSocket, NULL, NULL)) != INVALID_SOCKET) {
				system("cls");
				cout << "Client has connected" << endl;
				memset(recvBuffer, 0, 512);
				if (recv(clientSocket, recvBuffer, 512, 0) > 0) {
					string request = recvBuffer;
	
					CH.addUserToQueue(request, clientSocket);
				}
			}
			else {
				cout << "(!) accept error\n";
			}
		}
	}
	
	freeaddrinfo(addrResult);
	closesocket(listenSocket);
	WSACleanup();
}

