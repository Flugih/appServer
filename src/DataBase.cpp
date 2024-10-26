#include "../include/DataBase.h"

DataBase::DataBase()
{
    DB = nullptr;
    connectDB();
    createDB();
}

DataBase::~DataBase() {
    if (DB)
        closeDB();
}

int DataBase::callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        //cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    //cout << endl;
    return 0;
}

void DataBase::closeDB() {
    sqlite3_close(DB);
    cout << "Closed Database Successfully!" << endl;
}

void DataBase::createDB() {
    string query = "CREATE TABLE UsersData("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "USER_ID TEXT , "
        "OSversion TEXT , "
        "Region TEXT, "
        "AppVersion TEXT)";

    char* messaggeError;
    if (sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError) != SQLITE_OK) {
        cerr << "SQL error: " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else {
        cout << "Database Created" << endl;
    }
}

void DataBase::connectDB() {
    if (sqlite3_open("example.db", &DB))
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
    else
        cout << "Opened Database Successfully!" << endl;
}

void DataBase::addUser(string ID, map<string, string> acceptedData) {
    string query = "INSERT INTO UsersData (USER_ID, OSversion, Region, AppVersion) VALUES('" + ID + "', '" + acceptedData["OSversion"] + "', '" + acceptedData["region"] + "', '" + acceptedData["appVersion"] + "');"; // create query

    char* messaggeError;
    if (sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError) != SQLITE_OK) {
        cerr << "SQL error: " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else {
        cout << "User added successfully" << endl;
    }
}

int DataBase::checkID(string ID) { // finding userID in database, if return error, user is not in database
    cout << "check ID" << endl;
    bool userExists = false;
    string query = "SELECT * FROM UsersData WHERE USER_ID = '" + ID + "';";
    char* messaggeError;
    if (sqlite3_exec(DB, query.c_str(), NULL, &userExists, &messaggeError) != SQLITE_OK) {
        cerr << "SQL error: " << messaggeError << endl;
        sqlite3_free(messaggeError);
        return 1;
    }
    return userExists ? 0 : 1;
}

void DataBase::connect() {
    connectDB();
    createDB();
}

int DataBase::checkValidateID(string ID, map<string, string> acceptedData) { // if ID is validate, call "addUser" func
    //connectDB();
    //createDB();
    cout << ID << endl;
    if (checkID(ID)) { // 1 = user isnt in database, 0 = user in database
        addUser(ID, acceptedData);
        SD.sendUserID(ID);
        //closeDB();
        return 1;
    }
    //addUser(ID, acceptedData);
    //closeDB();
    return 0;
}
