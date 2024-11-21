#include <WinSock2.h>
#include <WS2tcpip.h>

#include <windows.h>
#include <sstream>
#include "../include/Connect.h"

using namespace std;
 
int main() {
	srand((unsigned)time(NULL));
	Connect con;
	con.startServer();
}
