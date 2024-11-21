#include <locale>

#include "../include/Connect.h"


using namespace std;

int main(){
	setlocale(LC_ALL, "ru");

	Connect con;
	con.client();

	return 0;
}
