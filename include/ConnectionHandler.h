#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <WinSock2.h>
#include <mutex>
#include <list>
#include <string>
#include "RequestProcessing.h"
#include "Serialization.h"
#include "UsersQueue.h"
#include <iostream>
#include <thread>

//#define WIN32_LEAN_AND_MEAN
//#pragma comment(lib, "WS2_32.lib")
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class ConnectionHandler {
private:
	RequestProcessing reqProc;
	Serialization deserialize;

	mutex mtx;

	void queueHandler();

public:
	void startQueueHandler();

	void addUserToQueue(string request, SOCKET socket);

	SOCKET getCurrentSocket() const;
};

#endif 