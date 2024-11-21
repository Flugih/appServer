#include "../include/sendingData.h"
#include "../include/Connect.h"
#include "../include/Serialization.h"
#include "../include/ClientInfo.h"
#include "../include/ClientInfoBlock.h"

Connect con;
Serialization serialization;
ClientInfo clin;

void SendingData::sendSystemInfo(){
	SOCKET connectSocket = con.getSocket();

	clin.getUserInfo();

	map<string, string> Info;

	for (clientData::iterator it = clInfo.begin(); it != clInfo.end(); ++it) {
		Info["requestType"] = "data";  // data or request
		Info["userID"] = it->userID;
		Info["OSversion"] = it->OSversion;
		Info["region"] = it->region;
		Info["appVersion"] = it->appVersion;
	}

	string serizlizedInfo = serialization.serialize(Info);
	Info.clear();

	if (send(connectSocket, serizlizedInfo.c_str(), (int)serizlizedInfo.size(), 0) == SOCKET_ERROR) {
		cerr << "Send failed: " << WSAGetLastError() << endl;
	}
	else {
		cout << "(!) Data sent successfully" << endl;
	}

}
