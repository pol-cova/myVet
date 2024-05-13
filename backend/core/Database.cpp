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
    const char* sql = "SELECT UserID, Username, Rol, Email FROM Users WHERE Username = ?";
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
    // Get the user ID, Username, Role and Email
    int userID = sqlite3_column_int(stmt, 0);
    string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    string mail = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    sqlite3_finalize(stmt);
    // convert userID to string
    string ID = to_string(userID);
    // Generate the JWT token
    return generateJWT(user, role, ID, mail);
}

bool Database::insertAppointment(const string &petname, const string &date, const string &hour, const string &service,
                                 const string &mail, const string &phone, const string &name) {
    const char* sql = "INSERT INTO Appointments (PetName, AppointmentDate, AppointmentTime, Email, Phone, Service, OwnerName) VALUES (?, ?, ?, ?, ?, ?, ?)";

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

bool Database::insertPet(const string &name, const int age, const string &type, const string &genre, const int userID) {
    const char* sql = "INSERT INTO Pets (Name, Age, Tipo, Genre, UserID) VALUES (?, ?, ?, ?, ?)";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, age);
    sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, genre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, userID);

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

int Database::countPetByUser(const int userID) {
    const char* sql = "SELECT COUNT(*) FROM Pets WHERE UserID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return -1;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, userID);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Get the count
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

int Database::countAppointmentsByUser(const string &mail) {
    const char* sql = "SELECT COUNT(*) FROM Appointments WHERE Email = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return -1;
    }
    // Bind the values
    sqlite3_bind_text(stmt, 1, mail.c_str(), -1, SQLITE_STATIC);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Get the count
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

vector<Pet> Database::getPetsByUser(const int userID) {
    vector<Pet> pets;
    const char* sql = "SELECT PetID, Name, Age, Tipo, Genre FROM Pets WHERE UserID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return pets;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, userID);
    // Exec the query
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int petID = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string genre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        pets.emplace_back(petID, name, age, type, genre);
    }
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    return pets;
}

bool Database::deletePet(const int petID) {
    const char* sql = "DELETE FROM Pets WHERE PetID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, petID);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error deleting data: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    return true;
}
// with Status 0
int Database::countAllAppointments() {
    const char* sql = "SELECT COUNT(*) FROM Appointments WHERE Status = 0";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return -1;
    }
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Get the count
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;

}

vector<Cita> Database::getAppointments() {
    // get all appointments
    vector<Cita> appointments;
    const char* sql = "SELECT * FROM Appointments";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return appointments;
    }
    // Exec the query
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int citaID = sqlite3_column_int(stmt, 0);
        string petname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string hour = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        string service = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        int status = sqlite3_column_int(stmt, 8);
        appointments.emplace_back(citaID, petname, date, hour, phone, service, name, status);
    }
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    return appointments;
}

int Database::countAllPets() {
    const char* sql = "SELECT COUNT(*) FROM Pets";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return -1;
    }
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Get the count
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

vector<Pet> Database::getPets() {
    vector<Pet> pets;
    const char* sql = "SELECT PetID, Name, Age, Tipo, Genre FROM Pets";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return pets;
    }
    // Exec the query
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int petID = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string genre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        pets.emplace_back(petID, name, age, type, genre);
    }
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    return pets;
}

int Database::countAllUsers() {
    const char* sql = "SELECT COUNT(*) FROM Users";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return -1;
    }
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Get the count
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

int Database::countAllAppointmentsDone() {
    const char* sql = "SELECT COUNT(*) FROM Appointments WHERE Status = 1";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return -1;
    }
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    // Get the count
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

bool Database::updateAppointmentStatus(const int appointmentID) {
    const char* sql = "UPDATE Appointments SET Status = 1 WHERE AppointmentID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, appointmentID);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error updating data: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    return true;
}

