#ifndef CONNECT_H
#define CONNECT_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <iostream>
#include <string>


#include "ConnectionHandler.h"

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "WS2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Connect {
private:
	ConnectionHandler CH;
public:
	void startServer();
};

#endif
