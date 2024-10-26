#ifndef USERSQUEUE_H
#define USERSQUEUE_H

#include <string>
#include <WinSock2.h>
#include <list>

using namespace std;

class UsersQueue {
public:
    string request;
    SOCKET clientSocket;

    UsersQueue(string req, SOCKET sock);
};

typedef list<UsersQueue> usQu;
extern usQu connectionQueue;

#endif 