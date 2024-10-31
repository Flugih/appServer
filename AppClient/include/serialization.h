#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <string>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

class Serialization {
private:
	string stringToHex(const string& str);

	string unification(map<string, string> data);

public:
	string serialize(map<string, string> data);
};

#endif