#include "../include/serialization.h"

string Serialization::stringToHex(const string& str){
	ostringstream oss;
	for (char c : str) {
		oss << hex << setw(2) << setfill('0') << static_cast<int>(static_cast<unsigned char>(c)) << " ";
	}
	return oss.str();
}

string Serialization::unification(map<string, string> data){
	string a;
	for (const auto& element : data) {
		a += "{" + element.first + ":" + element.second + "}";
	}

	data.clear();
	string hexStr = stringToHex(a);

	return hexStr;
}

string Serialization::serialize(map<string, string> data){
	return unification(data);
}
