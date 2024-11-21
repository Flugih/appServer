#include "../include/ResponseProcessing.h"
#include "../include/Serialization.h"
#include "../include/Connect.h"

ResponseProcessing::ResponseProcessing(){
	thread(&ResponseProcessing::acceptingResponses, this).detach();
}

void ResponseProcessing::acceptingResponses(){
	Connect con;
	Serialization ser;

	char recvBuffer[512];

	while (true) {
		SOCKET connectSocket = con.getSocket();

		memset(recvBuffer, 0, 512);
		if (recv(connectSocket, recvBuffer, 512, 0) > 0) {
			string deserialisedResponse = ser.deserialize(recvBuffer);
			map <string, string> b = ser.responseStringToMap(deserialisedResponse);
			for (auto& a : b) {
				cout << a.first << ": " << a.second << endl;
			}
			cout << "(!) Waiting server" << endl;
		}
		Sleep(10);
	}
}

void ResponseProcessing::distribution(){

}


	