//
// Created by Paul Contreras on 28/04/24.
//

#ifndef BACKEND_DATABASE_H
#define BACKEND_DATABASE_H

#include <iostream>
#include <string>
#include <sqlite3.h>

class Pet {
public:
    int petID;
    std::string name;
    int age;
    std::string type;
    std::string genre;
    // Owner Name and Owner id
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

    Tratamiento(const int tratamientoId,const std::string &tratamiento, const std::string &date, int petID, int userID, int medID, float cost, const std::string &ownerName, const std::string &petName, const int status)
            :tratamientoID(tratamientoId), tratamiento(tratamiento), date(date), petID(petID), userID(userID), medID(medID), cost(cost), OwnerName(ownerName), PetName(petName), Status(status) {};;
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

    // Appointments logic

    // new appointment
    bool insertAppointment(const string &petname, const string &date, const string &hour, const string &service,
                           const string &mail, const string &phone, const string &name);
    // count appointments by user using his mail
    int countAppointmentsByUser(const string &mail);

    // count all appointments with status 0
    int countAllAppointments();
    // count all appointments with status 1
    int countAllAppointmentsDone();

    // get all information of appointments store in vector type cita
    vector<Cita> getAppointments();

    // update status of appointment
    bool updateAppointmentStatus(const int appointmentID);


    // Pet logic

    // new pet
    bool insertPet(const string &name, const int age, const string &type, const string &genre, const int userID);
    // count pet by user
    int countPetByUser(const int userID);

    // get all information of user pets store in vector type pet
    vector<Pet> getPetsByUser(const int userID);
    // delete a pet from id
    bool deletePet(const int petID);

    // count all pets
    int countAllPets();
    // get all information of pets store in vector type pet
    vector<Pet> getPets();

    // get Owner from petID
    string getOwnerFromPetID(const int petID);
    // retrieve userID from petID
    int getUserIDFromPetID(const int petID);
    // update pet information Weight and Height
    bool updatePetInfo(const int petID, const int weight, const int height);


    // users logic

    // count all users
    int countAllUsers();


    // tratamientos logic

    // Insert a new Tratamiento
    bool insertTratamiento(const string &tratamiento, const string &date, const int petID,
                           const int userID, const int medID, const float cost);

    // get all information of tratamientos store in vector type tratamiento
    vector<Tratamiento> getTratamientos();

    // update status of tratamiento
    bool updateTratamientoStatus(const int tratamientoID);

    // facturas logic

    // Insert a new Factura
    /*
     * TratamientoID
        TotalCost
        DateOfEmision
        OwnerID
     */
    bool insertFactura(const int tratamientoID, const float totalCost, const string &date, const int ownerID);

    // get all information of facturas store in vector type factura
    vector<Factura> getFacturas();

    // update factura status
    bool updateFacturaStatus(const int facturaID);













private:
    const char* dbFileName_;
    sqlite3* db_;
};


#endif //BACKEND_DATABASE_H
