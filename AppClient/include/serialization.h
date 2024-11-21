#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <string>
#include <sstream>
#include <map>

using namespace std;

class Serialization {
private:
	map<string, string> acceptedData = {
		{"userID", "unknown"}, {"serverTime", "unknown"}, {"serverVersion", "0.1"}, {"response", "null"}
	};

	string hexToString(const string& hexStr);
	string stringToHex(const string& str);
	string unification(map<string, string> data);
	void stringToMap(string separatedString);
	void separationRequestData(string recvRequest);

public:
	string serialize(map<string, string> data);
	string deserialize(string data);
	map<string, string> responseStringToMap(string request);
};

#endif 
