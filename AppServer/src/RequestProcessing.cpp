#include "../include/RequestProcessing.h"

RequestProcessing::RequestProcessing() : actualVersion("1.0.0") {
}

void RequestProcessing::stringToMap(string separatedString) {
    string key = separatedString.substr(0, separatedString.find(":")), meaning = separatedString.substr(separatedString.find(":") + 1, separatedString.back());

    acceptedData[key] = meaning;
}

void RequestProcessing::separationRequestData(string recvRequest) {
    string separatedString;
    cout << "separationRequestData" << endl;

    if (!recvRequest.empty()) {
        while (true) {
            if (!recvRequest.empty()) {
                for (size_t i = recvRequest.find("{") + 1; i < recvRequest.find("}"); i++) {
                    separatedString += recvRequest[i];
                }
                recvRequest.erase(recvRequest.find("{"), recvRequest.find("}") + 1);
                stringToMap(separatedString);
                separatedString.clear();
            }
            else {
                break;
            }
        }
    }
}

void RequestProcessing::checkID() {
    if (acceptedData["userID"] == "unknown" || acceptedData["userID"] == "") {
        cout << "ID is unknown" << endl;
        createID();
    }
}

void RequestProcessing::createID() {
    cout << "Create id" << endl;

    string ID = "";
    bool exit = false;
    while (!exit) {
        ID = "";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ID += char(rand() % (90 - 65 + 1) + 65);
            }
            if (i < 3) {       
                ID += "-";
            }
        }
       exit = db.checkValidateID(ID, acceptedData);
    }

    if (!ID.empty())
        acceptedData["userID"] = ID;
}

string RequestProcessing::dataRequest() {
    cout << "dataRequest" << endl;
    checkID();
    return "";
}

void RequestProcessing::acceptData() {
    cout << "acceptData" << endl;
    checkID();
}

string RequestProcessing::distribution(string recvRequest) {
    AutoUpdate AU;
    cout << "distribution" << endl;
    separationRequestData(recvRequest);

    if (acceptedData["appVersion"] != actualVersion) {
        AU.updateClient();
        return "update"; // client needed update app
    }

    if (acceptedData["requestType"] == "data") {
        acceptData();
        return "accepted"; // server successfull accepted sended data
    }
    else if (acceptedData["requestType"] == "request") {
        return dataRequest(); // send data from dataRequest()
    }

    return ""; // Default return value
}
