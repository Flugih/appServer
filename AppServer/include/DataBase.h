#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <map>

using namespace std;

class DataBase {
private:
    sqlite3* DB;

    int callback(void* data, int argc, char** argv, char** azColName);
    void closeDB();
    void createDB();
    void connectDB();
    void addUser(string ID, map<string, string> acceptedData);
    int checkID(string ID);

public:
    DataBase();
    ~DataBase();
    //void connect();
    int checkValidateID(string ID, map<string, string> acceptedData);
};

#endif 
