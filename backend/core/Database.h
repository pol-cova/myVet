//
// Created by Paul Contreras on 28/04/24.
//

#ifndef BACKEND_DATABASE_H
#define BACKEND_DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

class Pet {
public:
    int petID;
    std::string name;
    int age;
    std::string type;
    std::string genre;
    std::string OwnerName;
    int OwnerID;

    Pet(int petID, const std::string& name, int age, const std::string& type, const std::string& genre, const std::string& ownerName, int ownerID)
            : petID(petID), name(name), age(age), type(type), genre(genre), OwnerName(ownerName), OwnerID(ownerID) {}
};

class Cita {
public:
    int AppointmentID;
    std::string PetName;
    std::string AppointmentDate;
    std::string AppointmentTime;
    std::string Phone;
    std::string Service;
    std::string OwnerName;
    int Status;

    Cita(int appointmentID, const std::string &petName, const std::string &appointmentDate,
         const std::string &appointmentTime, const std::string &phone, const std::string &service,
         const std::string &ownerName, int status)
            : AppointmentID(appointmentID), PetName(petName), AppointmentDate(appointmentDate),
              AppointmentTime(appointmentTime), Phone(phone), Service(service),
              OwnerName(ownerName), Status(status) {}
};

class Tratamiento {
public:
    int tratamientoID;
    std::string tratamiento;
    std::string date;
    int petID;
    int userID;
    int medID;
    float cost;
    std::string OwnerName;
    std::string PetName;
    int Status;

    Tratamiento(const int tratamientoId, const std::string &tratamiento, const std::string &date, int petID, int userID, int medID, float cost, const std::string &ownerName, const std::string &petName, const int status)
            : tratamientoID(tratamientoId), tratamiento(tratamiento), date(date), petID(petID), userID(userID), medID(medID), cost(cost), OwnerName(ownerName), PetName(petName), Status(status) {}
};

class PetTratamiento {
public:
    int petID;
    std::string tratamiento;
    std::string date;
    float cost;

    PetTratamiento(int petID, const std::string &tratamiento, const std::string &date, float cost)
            : petID(petID), tratamiento(tratamiento), date(date), cost(cost) {}
};

class Factura {
public:
    int FacturaID;
    std::string OwnerName;
    std::string Date;
    float Cost;
    int Status;

    Factura(int facturaID, const std::string &ownerName, const std::string &date, float cost, int status)
            : FacturaID(facturaID), OwnerName(ownerName), Date(date), Cost(cost), Status(status) {}
};

class Database {
public:
    Database(const std::string& dbFileName) : dbFileName_(dbFileName), db_(nullptr) {
        int rc = sqlite3_open(dbFileName.c_str(), &db_);
        if (rc) {
            std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db_) << std::endl;
        }
    }

    ~Database() {
        if (db_) {
            sqlite3_close_v2(db_);
        }
    }

    // Disable copy semantics to prevent double-free of sqlite3 connection
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // Enable move semantics
    Database(Database&& other) noexcept : dbFileName_(std::move(other.dbFileName_)), db_(other.db_) {
        other.db_ = nullptr;
    }
    Database& operator=(Database&& other) noexcept {
        if (this != &other) {
            if (db_) {
                sqlite3_close_v2(db_);
            }
            dbFileName_ = std::move(other.dbFileName_);
            db_ = other.db_;
            other.db_ = nullptr;
        }
        return *this;
    }

    // Auth logic
    bool insertUser(const std::string &username, const std::string &password, const std::string &salt, const std::string &email,
                    const std::string &role, const std::string &phone, const std::string &name);
    bool loginUser(const std::string &username, const std::string &password);
    std::string getUserToken(const std::string &username);

    // Appointments logic
    bool insertAppointment(const std::string &petname, const std::string &date, const std::string &hour, const std::string &service,
                           const std::string &mail, const std::string &phone, const std::string &name);
    int countAppointmentsByUser(const std::string &mail);
    int countAllAppointments();
    int countAllAppointmentsDone();
    std::vector<Cita> getAppointments();
    bool updateAppointmentStatus(const int appointmentID);

    // Pet logic
    bool insertPet(const std::string &name, const int age, const std::string &type, const std::string &genre, const int userID);
    int countPetByUser(const int userID);
    std::vector<Pet> getPetsByUser(const int userID);
    bool deletePet(const int petID);
    int countAllPets();
    std::vector<Pet> getPets();
    std::string getOwnerFromPetID(const int petID);
    int getUserIDFromPetID(const int petID);
    bool updatePetInfo(const int petID, const int weight, const int height);

    // Users logic
    int countAllUsers();

    // Tratamientos logic
    bool insertTratamiento(const std::string &tratamiento, const std::string &date, const int petID,
                           const int userID, const int medID, const float cost);
    std::vector<Tratamiento> getTratamientos();
    bool updateTratamientoStatus(const int tratamientoID);

    // Facturas logic
    bool insertFactura(const int tratamientoID, const float totalCost, const std::string &date, const int ownerID);
    std::vector<Factura> getFacturas();
    bool updateFacturaStatus(const int facturaID);

    // Ventas logic
    bool insertVenta(const std::string &date, const std::string &concepto, const int userID,
                     const float monto, const float cambio, const float recibido);
    float totalVentas(const std::string &date);
    int countVentas(const std::string &date);
    std::vector<PetTratamiento> getTratamientosByPetID(const int petID);

private:
    std::string dbFileName_;
    sqlite3* db_;
};

#endif //BACKEND_DATABASE_H
