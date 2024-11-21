#include "../include/Connect.h"
#include "../include/ConnectionHandler.h"
//#include "../include/DataBase.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <thread>

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "WS2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

ConnectionHandler CH;
//DataBase DB;

SOCKET listenSocket = INVALID_SOCKET;

const char* PORT = "5461";

//Connect::Connect() {
//	
//}

void Connect::startServer()
{
	//DB.connect();
	thread(&ConnectionHandler::queueHandler, &CH).detach();

	WSADATA wsaData;
	ADDRINFO hints;
	ADDRINFO* addrResult = NULL;
	SOCKET clientSocket = INVALID_SOCKET;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "(!) WSAStartup error\n";
		WSACleanup();
	}
	else if (getaddrinfo(NULL, PORT, &hints, &addrResult) != 0) { // here is the IP address and the port on which the server will work
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
		CH.incomingConnections();
	}

	freeaddrinfo(addrResult);
	closesocket(listenSocket);
	WSACleanup();
}

SOCKET Connect::getListenSocket(){
	return listenSocket;
}

