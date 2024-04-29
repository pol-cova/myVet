//
// Created by Paul Contreras on 28/04/24.
//

#ifndef BACKEND_DATABASE_H
#define BACKEND_DATABASE_H

#include <iostream>
#include <string>
#include <sqlite3.h>

class Database {
public:
    Database(const char* dbFileName) : dbFileName_(dbFileName), db_(nullptr) {
        int rc = sqlite3_open(dbFileName, &db_);
        if (rc) {
            std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db_) << std::endl;
        }
    }


    ~Database() {
        if (db_) {
            sqlite3_close(db_);
        }
    }
    // db logic
    // auth logic sys
    // register users
    bool insertUser(const string &username, const string &password, const string &salt, const string &email,
                    const string &role, const string &phone, const string &name);
    // login users
    bool loginUser(const string &username, const string &password);
    // get user JWT token
    string getUserToken(const string &username);

    // new appointment logic
    bool insertAppointment(const string &petname, const string &date, const string &hour, const string &service,
                           const string &mail, const string &phone, const string &name);


private:
    const char* dbFileName_;
    sqlite3* db_;
};


#endif //BACKEND_DATABASE_H
