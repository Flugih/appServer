#include "../include/Serialization.h"

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
