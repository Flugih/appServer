#include "../include/RequestProcessing.h"
#include "../include/DataBase.h"
#include "../include/AutoUpdate.h"
#include "../include/Serialization.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

DataBase db;
Serialization ser;

RequestProcessing::RequestProcessing() : actualVersion("1.0.0") {
}

void RequestProcessing::checkID(map<string, string> acceptedData) {
    // map<string, string> acceptedData = ser.
    if (acceptedData["userID"] == "unknown" || acceptedData["userID"] == "") {
        cout << "ID is unknown" << endl;
        createID(acceptedData);
    }
}

void RequestProcessing::createID(map<string, string> acceptedData) {
    cout << "Create id" << endl;

    string ID = "";
    bool exit = false;
    while (!exit) {
        ID = "";
        for (uint32_t i = 0; i < 5; i++) {
            for (uint32_t j = 0; j < 4; j++) {
                ID += char(rand() % (90 - 65 + 1) + 65);
            }
        }
       exit = db.checkValidateID(ID, acceptedData);
    }

    if (!ID.empty())
        acceptedData["userID"] = ID;
}

string RequestProcessing::dataRequest(map<string, string> acceptedData) {
    cout << "dataRequest" << endl;
    checkID(acceptedData);
    return "";
}

void RequestProcessing::acceptData(map<string, string> acceptedData) {
    cout << "acceptData" << endl;
    checkID(acceptedData);
}

string RequestProcessing::distribution(string recvRequest) {
    AutoUpdate AU;
    cout << "distribution" << endl;
    map<string, string> acceptedData = ser.resqustStringToMap(recvRequest);

    if (acceptedData["appVersion"] != actualVersion) {
        AU.updateClient();
        return "update"; // client needed update app
    }

    if (acceptedData["requestType"] == "data") {
        acceptData(acceptedData);
        return "accepted"; // server successfull accepted sended data
    }
    else if (acceptedData["requestType"] == "request") {
        return dataRequest(acceptedData); // send data from dataRequest()
    }

    return ""; // Default return value
}
