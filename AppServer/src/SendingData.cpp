#include "../include/SendingData.h"
#include "../include/ConnectionHandler.h" 

void SendingData::sendUserID(string ID) {
    cout << "send data" << endl;
    send(CH->getCurrentSocket(), ID.c_str(), (int)ID.size(), 0);
}
