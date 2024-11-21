#include "../include/Serialization.h"

#include <iomanip>
#include <iostream>

void Serialization::stringToMap(string separatedString) {
	string key = separatedString.substr(0, separatedString.find(":")), meaning = separatedString.substr(separatedString.find(":") + 1, separatedString.back());

	acceptedData[key] = meaning;
}

void Serialization::separationRequestData(string recvRequest) {
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

string Serialization::hexToString(const string& hexStr)
{
	string result;
	istringstream iss(hexStr);
	string byte;
	
	while (iss >> byte) {
		unsigned char ch = static_cast<unsigned char>(stoi(byte, nullptr, 16));
		result += ch;
	}
	
	return result;
}

string Serialization::stringToHex(const string& str) {
	ostringstream oss;
	for (char c : str) {
		oss << hex << setw(2) << setfill('0') << static_cast<int>(static_cast<unsigned char>(c)) << " ";
	}
	return oss.str();
}

string Serialization::unification(map<string, string> data) {
	string a;
	for (const auto& element : data) {
		a += "{" + element.first + ":" + element.second + "}";
	}

	data.clear();

	return stringToHex(a);
}

string Serialization::serialize(map<string, string> data) {
	return unification(data);
}

string Serialization::deserialize(string data)
{
	return hexToString(data);
}

map<string, string> Serialization::resqustStringToMap(string request)
{
	separationRequestData(request);
	return acceptedData;
}
