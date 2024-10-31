#include "../include/Connect.h"

void Connect::tryAgain() {
	Sleep(5000);
	client();
}

void Connect::sendInfo() const {
	Serialization serialization;
	ClientInfo clin;
	clin.getUserInfo();

	map<string, string> Info;

	for (clientData::iterator it = clInfo.begin(); it != clInfo.end(); ++it) {
		Info["requestType"] = "data";  // data or request
		Info["userID"] = it->userID;
		Info["OSversion"] = it->OSversion;
		Info["region"] = it->region;
		Info["appVersion"] = it->appVersion;
	}

	// serialization.Info = Info;
	string serizlizedInfo = serialization.serialize(Info);
	Info.clear();
	cout << serizlizedInfo << endl;

	send(connectSocket, serizlizedInfo.c_str(), (int)serizlizedInfo.size(), 0);
}

void Connect::client() {
	WSADATA wsaData;
	ADDRINFO hints;
	ADDRINFO* addrResult = NULL;
	SOCKET clientSocket = INVALID_SOCKET;
	// string command;

	char recvBuffer[512];

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 1) {
		cout << "(!) WSAStartup error\n";
		WSACleanup();
		tryAgain();
	}
	else if (getaddrinfo("localhost", "5461", &hints, &addrResult) == 1) {
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
		sendInfo();

		while (true) {
			memset(recvBuffer, 0, 512);
			if (recv(connectSocket, recvBuffer, 512, 0) > 0) {
				cout << recvBuffer;
			}
			Sleep(1000);
		}
	}
}

SOCKET Connect::getSocket() {
	return connectSocket;
}
