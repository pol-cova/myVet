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

bool Database::loginUser(const string &username, const string &password) {
    // First check if user exists
    const char* sql = "SELECT Password, Salt FROM Users WHERE Username = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Exec the query
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    // Get the password and salt
    string dbPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    string dbSalt = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    sqlite3_finalize(stmt);
    // Validate the password
    if (validatePassword(password, dbPassword, dbSalt)) {
        return true;
    }
    // If the password is invalid
    return false;
}

string Database::getUserToken(const string &username) {
    // Get the user ID, Username and Role
    const char* sql = "SELECT UserID, Username, Rol FROM Users WHERE Username = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return "";
    }
    // Exec the query
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return "";
    }
    // Get the user ID, Username and Role
    int userID = sqlite3_column_int(stmt, 0);
    string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    sqlite3_finalize(stmt);
    // convert userID to string
    string ID = to_string(userID);
    // Generate the JWT token
    return generateJWT(user, role, ID);
}

bool Database::insertAppointment(const string &petname, const string &date, const string &hour, const string &service,
                                 const string &mail, const string &phone, const string &name) {
    const char* sql = "INSERT INTO Appointments (PetName, AppointmentDate, AppointmentDate, Email, Phone, Service, OwnerName) VALUES (?, ?, ?, ?, ?, ?, ?)";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_text(stmt, 1, petname.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, hour.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, mail.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, phone.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, service.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, name.c_str(), -1, SQLITE_STATIC);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    return true;
}
