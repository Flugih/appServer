#ifndef CONNECT_H
#define CONNECT_H

#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

class Connect {
private:
public:
	void startServer();
	SOCKET getListenSocket();

	/*Connect();*/
};

#endif