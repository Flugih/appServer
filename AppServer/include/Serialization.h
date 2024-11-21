#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <string>
#include <sstream>
#include <map>

using namespace std;

class Serialization {
private:
	map<string, string> acceptedData = {
		{"requestType", "unknown"}, {"userID", "unknown"}, {"OSversion", "unknown"}, {"region", "unknown"}, {"appVersion", "unknown"}
	};

	string hexToString(const string& hexStr);
	string stringToHex(const string& str);
	string unification(map<string, string> data);
	void stringToMap(string separatedString);
	void separationRequestData(string recvRequest);

public:
	string serialize(map<string, string> data);
	string deserialize(string data);
	map<string, string> resqustStringToMap(string request);
};

#endif 
