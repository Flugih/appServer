#include "../include/SendingData.h"
#include "../include/ConnectionHandler.h" 
#include "../include/Serialization.h" 

#include <iostream>
#include <WinSock2.h>
#include <chrono>
#include <ctime>

void SendingData::sendResponse(string ID, string response){
    ConnectionHandler CH;
    Serialization ser;

    auto timeNow = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(timeNow);
    char buffer[26];
    if (ctime_s(buffer, sizeof(buffer), &time) == 0) {
        buffer[strlen(buffer) - 1] = '\0';
    }
    responseData["userID"] = ID;
    responseData["serverTime"] = buffer;
    responseData["response"] = response;

    //cout << buffer << endl;

    string serizlizedData = ser.serialize(responseData);

    cout << "send data" << endl;
    send(CH.getCurrentSocket(), serizlizedData.c_str(), (int)serizlizedData.size(), 0);
}
