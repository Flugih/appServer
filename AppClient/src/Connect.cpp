#include "../include/Connect.h"
#include "../include/SendingData.h"
#include "../include/ResponseProcessing.h"
#include "../include/ClientInfo.h"
#include "../include/Serialization.h"

SendingData SD;
ResponseProcessing RP;

SOCKET connectSocket = INVALID_SOCKET;

const char* PORT = "5461";
const char* ADDRESS = "localhost";

void Connect::tryAgain() {
	Sleep(5000);
	client();
}

void Connect::client() {

	WSADATA wsaData;
	ADDRINFO hints;
	ADDRINFO* addrResult = NULL;
	SOCKET clientSocket = INVALID_SOCKET;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 1) {
		cout << "(!) WSAStartup error\n";
		WSACleanup();
		tryAgain();
	}
	else if (getaddrinfo(ADDRESS, PORT, &hints, &addrResult) == 1) {
		cout << "(!) getaddrinfo error\n";
		WSACleanup();
		freeaddrinfo(addrResult);
		tryAgain();
	}
	else if ((connectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol)) == INVALID_SOCKET) {
		cout << "(!) socket error\n";
		WSACleanup();
		freeaddrinfo(addrResult);
		closesocket(connectSocket);
		tryAgain();
	}
	else if (connect(connectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen) == SOCKET_ERROR) {
		cout << "(!) connect error\n";
		WSACleanup();
		freeaddrinfo(addrResult);
		closesocket(connectSocket);
		tryAgain();
	}
	else {
		cout << "(!) successful connect :)" << endl;
		SD.sendSystemInfo();

		while (true) {
		}
	}

	WSACleanup();
	freeaddrinfo(addrResult);
	closesocket(connectSocket);
}

SOCKET Connect::getSocket() const {
	return connectSocket;
}
