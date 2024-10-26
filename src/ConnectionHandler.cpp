#include "../include/ConnectionHandler.h"

void ConnectionHandler::queueHandler() {
    //DataBase db;
    srand((unsigned)time(NULL));

    //reqProc.actualVersion = "0.0";
    cout << "queueHandler" << endl;
    // db.connect();

    while (true) {
        unique_lock<mutex> lock(mtx);
        usQu::iterator it = connectionQueue.begin();
        while (it != connectionQueue.end()) {
            string deserializedRequest = deserialize.hexToString(it->request);
            //cout << deserializedRequest << endl;
            string answer = reqProc.distribution(deserializedRequest);
            //if (!answer.empty()) {
            //	/*switch (answer) {
            //		case "":
            //	}*/
            //	// send answer to client with class SendingData
            //}
            it = connectionQueue.erase(it); // Удаляем текущий элемент и получаем новый итератор
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
