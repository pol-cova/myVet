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
    bool insertUser(const string &username, const string &password, const string &salt, const string &email,
                    const string &role, const string &phone, const string &name);
private:
    const char* dbFileName_;
    sqlite3* db_;
};


#endif //BACKEND_DATABASE_H
