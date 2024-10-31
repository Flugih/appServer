#ifndef REQUESTPROCESSING_H
#define REQUESTPROCESSING_H

#include <string>
#include <map>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "DataBase.h"
#include "AutoUpdate.h"

using namespace std;

class RequestProcessing {
private:
    DataBase db;
    string actualVersion;

    map<string, string> acceptedData = {
        {"requestType", "unknown"}, {"userID", "unknown"}, {"OSversion", "unknown"}, {"region", "unknown"}, {"appVersion", "unknown"}
    };

    void stringToMap(string separatedString);
    void separationRequestData(string recvRequest);
    void checkID();
    void createID();
    string dataRequest();
    void acceptData();

public:
    RequestProcessing();

    string distribution(string recvRequest);
};

#endif 
