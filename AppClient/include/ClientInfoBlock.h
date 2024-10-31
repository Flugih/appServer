#ifndef CLIENTINFOBLOCK_H
#define CLIENTINFOBLOCK_H

#include <list>
#include <string>

using namespace std;

class ClientInfoBlock { // class for creating data structure
public:
	string OSversion;
	string region;
	string appVersion;
	string userID;

	ClientInfoBlock(string osn, string reg, string app, string usrid) : OSversion(osn), region(reg), appVersion(app), userID(usrid) {}
};

typedef list<ClientInfoBlock> clientData;
extern clientData clInfo;

#endif