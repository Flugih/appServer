#ifndef CONNECT_H
#define CONNECT_H

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "WS2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Connect {
private:
	void tryAgain();

public:
	void client();
	SOCKET getSocket() const;

};

#endif
