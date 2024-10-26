#include "../include/SendingData.h"
#include "../include/ConnectionHandler.h" 

// SendingData::SendingData(ConnectionHandler* ch) : CH(ch) {}

void SendingData::sendUserID(string ID) {
    SOCKET clientSocket = CH->getCurrentSocket();
    send(clientSocket, ID.c_str(), (int)ID.size(), 0);
}