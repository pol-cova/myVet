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
    const char* sql = "SELECT PetID, Name, Age, Tipo, Genre, UserID FROM Pets WHERE UserID = ?";
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
        int ownerID = sqlite3_column_int(stmt, 5);
        // Assuming the owner's name is available in another variable
        string ownerName = getOwnerFromPetID(petID);
        pets.emplace_back(petID, name, age, type, genre, ownerName, ownerID);
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
    const char* sql = "SELECT Pets.PetID, Pets.Name, Pets.Age, Pets.Tipo, Pets.Genre, Users.Name, Users.UserID FROM Pets INNER JOIN Users ON Pets.UserID = Users.UserID";
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
        string ownerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        int ownerID = sqlite3_column_int(stmt, 6);
        pets.emplace_back(petID, name, age, type, genre, ownerName, ownerID);
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

string Database::getOwnerFromPetID(const int petID) {
    const char* sql = "SELECT Users.Name FROM Pets INNER JOIN Users ON Pets.UserID = Users.UserID WHERE Pets.PetID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    string owner;
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return owner;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, petID);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return owner;
    }
    // Get the owner name
    owner = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    sqlite3_finalize(stmt);
    return owner;
}

int Database::getUserIDFromPetID(const int petID) {
    const char* sql = "SELECT UserID FROM Pets WHERE PetID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    int userID = -1;
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return userID;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, petID);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return userID;
    }
    // Get the owner name
    userID = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return userID;
}

bool Database::insertTratamiento(const string &tratamiento, const string &date, const int petID,
                                 const int userID, const int medID, const float cost){
    const char* sql = "INSERT INTO Tratamientos (Tratamiento, DateOfTratamiento, PetID, OwnerUserID, MedUserID, Cost) VALUES (?, ?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_text(stmt, 1, tratamiento.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, petID);
    sqlite3_bind_int(stmt, 4, userID);
    sqlite3_bind_int(stmt, 5, medID);
    sqlite3_bind_double(stmt, 6, cost);
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

vector<Tratamiento> Database::getTratamientos() {
    vector<Tratamiento> tratamientos;
    const char* sql = "SELECT Tratamientos.TratamientoID, Tratamientos.Tratamiento, Tratamientos.DateOfTratamiento, Tratamientos.PetID, Tratamientos.OwnerUserID, Tratamientos.MedUserID, Tratamientos.Cost, Tratamientos.Status, Users.Name, Pets.Name FROM Tratamientos INNER JOIN Users ON Tratamientos.OwnerUserID = Users.UserID INNER JOIN Pets ON Tratamientos.PetID = Pets.PetID";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return tratamientos;
    }
    // Exec the query
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int tratamientoId = sqlite3_column_int(stmt, 0);
        string tratamiento = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int petID = sqlite3_column_int(stmt, 3);
        int userID = sqlite3_column_int(stmt, 4);
        int medID = sqlite3_column_int(stmt, 5);
        float cost = sqlite3_column_double(stmt, 6);
        int status = sqlite3_column_int(stmt, 7);
        string ownerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        string petName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        tratamientos.emplace_back(tratamientoId, tratamiento, date, petID, userID, medID, cost, ownerName, petName, status);
    }
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    return tratamientos;
}

bool Database::updateTratamientoStatus(const int tratamientoID) {
    const char* sql = "UPDATE Tratamientos SET Status = 1 WHERE TratamientoID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, tratamientoID);
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

bool Database::insertFactura(const int tratamientoID, const float totalCost, const string &date, const int ownerID) {
    const char* sql = "INSERT INTO Facturas (TratamientoID, TotalCost, DateOfEmision, OwnerID) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, tratamientoID);
    sqlite3_bind_double(stmt, 2, totalCost);
    sqlite3_bind_text(stmt, 3, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, ownerID);
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

vector<Factura> Database::getFacturas() {
    vector<Factura> facturas;
    const char* sql = "SELECT Facturas.FacturaID, Users.Name, Facturas.DateOfEmision, Facturas.TotalCost, Facturas.Status "
                      "FROM Facturas INNER JOIN Users ON Facturas.OwnerID = Users.UserID";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return facturas;
    }
    // Exec the query
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int facturaID = sqlite3_column_int(stmt, 0);
        string ownerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        float cost = sqlite3_column_double(stmt, 3);
        int status = sqlite3_column_int(stmt, 4);
        facturas.emplace_back(facturaID, ownerName, date, cost, status);
    }
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
    }
    // Finalize the statement
    sqlite3_finalize(stmt);
    return facturas;
}

bool Database::updateFacturaStatus(const int facturaID) {
    const char* sql = "UPDATE Facturas SET Status = 1 WHERE FacturaID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, facturaID);
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

bool Database::updatePetInfo(const int petID, const int weight, const int height) {
    const char* sql = "UPDATE Pets SET Weight = ?, Height = ? WHERE PetID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, weight);
    sqlite3_bind_int(stmt, 2, height);
    sqlite3_bind_int(stmt, 3, petID);
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

bool Database::insertVenta(const string &date, const string &concepto, const int userID,
                           const float monto, const float cambio, const float recibido){
    const char* sql = "INSERT INTO Ventas (userID, DateVenta, Concepto, Monto, Recibido, Cambio) VALUES (?, ?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    // Bind the values
    sqlite3_bind_int(stmt, 1, userID);
    sqlite3_bind_text(stmt, 2, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, concepto.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, monto);
    sqlite3_bind_double(stmt, 5, recibido);
    sqlite3_bind_double(stmt, 6, cambio);
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

float Database::totalVentas(const string &date) {
const char* sql = "SELECT SUM(Monto) FROM Ventas WHERE DateVenta = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    float total = 0.0;
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return total;
    }
    // Bind the values
    sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_STATIC);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return total;
    }
    // Get the total
    total = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);
    return total;
}

int Database::countVentas(const string &date) {
const char* sql = "SELECT COUNT(*) FROM Ventas WHERE DateVenta = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    int count = 0;
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db_) << std::endl;
        return count;
    }
    // Bind the values
    sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_STATIC);
    // Exec the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_finalize(stmt);
        return count;
    }
    // Get the count
    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}
