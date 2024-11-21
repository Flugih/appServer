#include "../include/DataBase.h"
#include "../include/SendingData.h"

#include <iostream>
#include <map>
#include <string>
#include <sqlite3.h>
#include <windows.h>

using namespace std;

SendingData SD;

DataBase::DataBase() {
    DB = nullptr;
    connectDB();
    createDB();
}

DataBase::~DataBase() {
    if (DB)
        closeDB();
}

//void DataBase::connect() {
//    DB = nullptr;
//    connectDB();
//    createDB();
//}

void DataBase::closeDB() {
    if (DB) {
        sqlite3_close(DB);
        DB = nullptr;
        cout << "Closed Database Successfully!" << endl;
    }
}

int DataBase::callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}


void DataBase::createDB() {
    /*if (!DB) {
        cerr << "Database is not open" << endl;
        return;
    }*/

    string query = "CREATE TABLE IF NOT EXISTS UsersData("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "USER_ID TEXT , "
        "OSversion TEXT , "
        "Region TEXT, "
        "AppVersion TEXT)";

    char* messageError;
    if (sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError) != SQLITE_OK) {
        cerr << messageError << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Database Created" << endl;
    }
}

void DataBase::connectDB() {
    if (sqlite3_open("usersData.db", &DB)) {
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
        DB = nullptr;
    }
    else {
        cout << "Opened Database Successfully!" << endl;
    }
}

void DataBase::addUser(string ID, map<string, string> acceptedData) {
    /*if (!DB) {
        cerr << "Database is not open" << endl;
        return;
    }*/

    string query = "INSERT INTO UsersData (USER_ID, OSversion, Region, AppVersion) VALUES('" + ID + "', '" + acceptedData["OSversion"] + "', '" + acceptedData["region"] + "', '" + acceptedData["appVersion"] + "');"; // create query

    char* messageError;
    if (sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError) != SQLITE_OK) {
        cerr << "SQL error: " << messageError << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "User added successfully" << endl;
    }
}

int DataBase::checkID(string ID) { // finding userID in database, if return error, user is not in database
   /* if (!DB) {
        cerr << "Database is not open" << endl;
        return 1;
    }*/

    cout << "check ID" << endl;
    //bool userExists = false;
    string query = "SELECT * FROM UsersData WHERE USER_ID = " + ID + ";";
    char* messageError;
    if (sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError) != SQLITE_OK) {
        cerr << "SQL error: " << messageError << endl;
        sqlite3_free(messageError);
        return 1;
    }
    else {
        return 0;
    }
    
}


int DataBase::checkValidateID(string ID, map<string, string> acceptedData) { // if ID is validate, call "addUser" func
    /*if (!DB) {
        cerr << "Database is not open" << endl;
        return 0;
    }*/

    //connect();

    cout << ID << endl;
    if (checkID(ID)) { // 1 = user isnt in database, 0 = user in database
        addUser(ID, acceptedData);
        //SD.sendUserID(ID);
        SD.sendResponse(ID, "123");
        return 1;
    }

    //closeDB();

    return 0;  // change to 0
}
