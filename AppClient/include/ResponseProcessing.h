#ifndef RESPONSEPROCESSING_H
#define RESPONSEPROCESSING_H

#include <thread>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

class ResponseProcessing {
private:
	void distribution();

public:
	void acceptingResponses();
	ResponseProcessing();
};

#endif