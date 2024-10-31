#include "../include/UsersQueue.h"

UsersQueue::UsersQueue(string req, SOCKET sock) : request(req), clientSocket(sock) {}

usQu connectionQueue;