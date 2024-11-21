#ifndef SENDINGDATA_H
#define SENDINGDATA_H

#include <string>
#include <map>

using namespace std;

class SendingData {
private:
    map<string, string> responseData = {
        {"userID", "unknown"}, {"serverTime", "unknown"}, {"serverVersion", "0.1"}, {"response", "null"}
    };
public:
    void sendResponse(string ID, string reponse);
};

#endif 
