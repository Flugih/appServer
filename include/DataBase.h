#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <map>
#include "sqlite3.h"
#include "SendingData.h"

using namespace std;

class DataBase {
private:
    SendingData SD;
    sqlite3* DB = nullptr;

    // sqlite3* DB = nullptr;

    int callback(void* data, int argc, char** argv, char** azColName);
    void closeDB();
    void createDB();
    void connectDB();
    void addUser(string ID, map<string, string> acceptedData);
    int checkID(string ID);

public:
    DataBase();
    ~DataBase();
    void connect();
    int checkValidateID(string ID, map<string, string> acceptedData);
};

#endif 
