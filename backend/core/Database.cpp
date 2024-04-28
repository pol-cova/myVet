//
// Created by Paul Contreras on 28/04/24.
//

#include "Database.h"

// insert user operation
bool Database::insertUser(const string &username, const string &password, const string &salt, const string &email,
                          const string &role, const string &phone, const string &name) {
    const char* sql = "INSERT INTO Users (Username, Password, Salt, Email, Rol, Phone, Name) VALUES (?, ?, ?, ?, ?, ?, ?)";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, salt.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, role.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, phone.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, name.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}
