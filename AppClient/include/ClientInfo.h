#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <string>
#include <windows.h>
#include <codecvt>
#include <sstream>
#include <iomanip>
#include "ClientInfoBlock.h"

constexpr auto COUNTRY_NAME_MAX_LEN = 80;

typedef LONG(WINAPI* RtlGetVersionPtr)(OSVERSIONINFOEX*);

using namespace std;

class ClientInfo {
private:
	string OSversion;
	string region;
	string appVersion;
	string userID = "";

	void collectUserInfo();

	void getOSversion();

	void getRegion();

public:
	ClientInfo();
	void getUserInfo();
};

#endif