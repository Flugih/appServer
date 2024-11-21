#include "../include/ConnectionHandler.h"
#include "../include/RequestProcessing.h"
#include "../include/Serialization.h"
#include "../include/UsersQueue.h"
#include "../include/Connect.h"
//#include "../include/DataBase.h"

#include <list>
#include <iostream>
#include <thread>

RequestProcessing reqProc;
//ConnectionHandler CH;
Connect con;
//DataBase DB;

SOCKET clientSocket = INVALID_SOCKET;
SOCKET clientSocketIncoming = INVALID_SOCKET;

//ConnectionHandler::ConnectionHandler() {
//    //thread(&ConnectionHandler::queueHandler, this).detach();
//}

void ConnectionHandler::queueHandler() {
    srand((unsigned)time(NULL));
    Serialization ser;
    //DB.connect();

    cout << "queueHandler" << endl;

    while (true) {
        if (!connectionQueue.empty()) {
            unique_lock<mutex> lock(mtx);
            usQu::iterator it = connectionQueue.begin();
            while (it != connectionQueue.end()) {
                clientSocket = it->clientSocket;
                string deserializedRequest = ser.deserialize(it->request);
                string answer = reqProc.distribution(deserializedRequest);
                if (!answer.empty()) {
                    if (answer == "update") {
                        // the script of AutoUpdate
                    }
                    else if (answer == "accepted") {
                        // the script of accepted data
                    }
                    else {
                        // the script of request data
                    }
                    // send answer to client with class SendingData
                }
                it = connectionQueue.erase(it);
            }
            lock.unlock();
        }
    }
}

void ConnectionHandler::incomingConnections(){
    char recvBuffer[512];

    SOCKET listenSocket = con.getListenSocket();

    while (true) {
        memset(recvBuffer, 0, 512);
        if ((clientSocketIncoming = accept(listenSocket, NULL, NULL)) != INVALID_SOCKET) {
            system("cls");
            cout << "Client has connected" << endl;
            if (recv(clientSocketIncoming, recvBuffer, 512, 0) > 0) {
                string request = recvBuffer;

                addUserToQueue(request, clientSocketIncoming);
            }
        }
        else {
            cout << "(!) accept error\n";
        }
    }
}

void ConnectionHandler::addUserToQueue(string request, SOCKET socket) {
    cout << "addUserToQueue" << endl;

    connectionQueue.push_back({ request, socket });
}

SOCKET ConnectionHandler::getCurrentSocket() const {
    return clientSocket;
}
