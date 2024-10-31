#ifndef CONNECT_H
#define CONNECT_H

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>

#include "ClientInfo.h"
#include "Serialization.h"

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "WS2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Connect {
private:
	SOCKET connectSocket = INVALID_SOCKET;

	void tryAgain();

	void sendInfo() const;

public:
	// SOCKET connectSocket = INVALID_SOCKET;

	void client();
	SOCKET getSocket();

};

#endif
