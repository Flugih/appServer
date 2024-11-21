#ifndef REQUESTPROCESSING_H
#define REQUESTPROCESSING_H

#include <map>
#include <string>

using namespace std;

class RequestProcessing {
private:
    string actualVersion;

    /*map<string, string> acceptedData = {
        {"requestType", "unknown"}, {"userID", "unknown"}, {"OSversion", "unknown"}, {"region", "unknown"}, {"appVersion", "unknown"}
    };*/

    //void stringToMap(string separatedString);
    //void separationRequestData(string recvRequest);
    void checkID(map<string, string> acceptedData);
    void createID(map<string, string> acceptedData);
    string dataRequest(map<string, string> acceptedData);
    void acceptData(map<string, string> acceptedData);

public:
    RequestProcessing();

    string distribution(string recvRequest);
};

#endif 
