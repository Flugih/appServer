#include "../include/ConnectionHandler.h"

SOCKET clientSocket = INVALID_SOCKET;

void ConnectionHandler::queueHandler() {
    srand((unsigned)time(NULL));

    cout << "queueHandler" << endl;

    while (true) {
        unique_lock<mutex> lock(mtx);
        usQu::iterator it = connectionQueue.begin();
        while (it != connectionQueue.end()) {
            clientSocket = it->clientSocket;
            string deserializedRequest = deserialize.hexToString(it->request);
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

void ConnectionHandler::startQueueHandler() {
    thread(&ConnectionHandler::queueHandler, this).detach();
}

void ConnectionHandler::addUserToQueue(string request, SOCKET socket) {
    cout << "addUserToQueue" << endl;

    connectionQueue.push_back({ request, socket });
}

SOCKET ConnectionHandler::getCurrentSocket() const {
    return clientSocket;
}
