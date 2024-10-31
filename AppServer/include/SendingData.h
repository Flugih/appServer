#ifndef SENDINGDATA_H
#define SENDINGDATA_H

#include <string>
#include <WinSock2.h>

using namespace std;

class ConnectionHandler;

class SendingData {
private:
    ConnectionHandler* CH;

public:
    // SendingData(ConnectionHandler* ch); 
    void sendUserID(string ID);
};

#endif 
