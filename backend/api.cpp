//
// Created by Paul Contreras on 09/05/24.
//
#include "crow.h"
#include "crow/middlewares/cors.h"

// STL libs
#include <chrono>
#include <ctime>
#include <unordered_set> // For efficient lookup of selected hours
#include <vector>
#include <string>

// import libraries for auth
#include "spark/spark.cpp"

// import libraries for database
#include "core/Database.cpp"

// import custom utils library
#include "utils/Citas.cpp"


int main()
{
    // Enable CORS
    crow::App<crow::CORSHandler> app;
    // custom cors
    auto& cors = app.get_middleware<crow::CORSHandler>();
    // SetUp CORS
    cors.global()
    .origin("http://localhost:5173") // replace with the origin your Vue.js app is running on
    .allow_credentials()
    .headers(
            "Accept",
            "Origin",
            "Content-Type",
            "Authorization",
            "Refresh"
    )
    .methods(
            crow::HTTPMethod::GET,
            crow::HTTPMethod::POST,
            crow::HTTPMethod::PUT,
            crow::HTTPMethod::DELETE,
            crow::HTTPMethod::OPTIONS,
            crow::HTTPMethod::HEAD
    );

    // Health route
    CROW_ROUTE(app, "/health")
    ([](){
        return crow::response(200, "OK");
    });

    // Hello world route
    CROW_ROUTE(app, "/hello")
    ([](){
        return crow::response(200, "Hello World!");
    });

    // Auth0 routes
    // Login
    CROW_ROUTE(app, "/auth/login")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request &req){
                        auto json_payload = crow::json::load(req.body);

                        if (!json_payload){
                            return crow::response(400, "Invalid JSON");
                        }

                        std::string user = json_payload["username"].s();
                        std::string password = json_payload["password"].s();

                        // auth logic
                        Database db("../core/app.db");
                        bool isLogged = db.loginUser(user, password);

                        if (!isLogged){
                            crow::json::wvalue res;
                            res["status"] = "Unauthorized";
                            res["msg"] = "Authentication failed";

                            crow::response response(401, "Unauthorized");
                            response.set_header("Access-Control-Allow-Origin", "*");
                            response.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
                            response.set_header("Access-Control-Allow-Headers", "Content-Type, X-Custom-Header");

                            return response;
                        }

                        // generate a JWT token
                        std::string token = db.getUserToken(user);

                        crow::json::wvalue res;
                        res["status"] = "OK";
                        res["msg"] = "User logged in successfully";
                        res["token"] = token;

                        crow::response response(200, res);
                        response.set_header("Access-Control-Allow-Origin", "*");
                        response.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
                        response.set_header("Access-Control-Allow-Headers", "Content-Type, X-Custom-Header");

                        return response;
                    });
    // Register
    CROW_ROUTE(app, "/auth/register")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request &req){

                        auto json_payload = crow::json::load(req.body);

                        if (!json_payload){
                            return crow::response(400, "Invalid JSON");
                        }

                        std::string name = json_payload["name"].s();
                        std::string user = json_payload["user"].s();
                        std::string mail = json_payload["mail"].s();
                        std::string phone = json_payload["phone"].s();
                        std::string password = json_payload["password"].s();

                        // auth logic
                        // generate a random salt
                        std::string salt = generate_salt();
                        // hash the password
                        std::string hash = hashPassword(password, salt);

                        // prepare for inserting in db
                        Database db("../core/app.db");
                        bool status;

                        status = db.insertUser(user, hash, salt, mail, "user", phone, name);

                        if (!status){
                            return crow::response(500, "Internal Server Error");
                        }

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "User created successfully"}
                                               });


                        return crow::response(200, res);
                    });

    // get all users count
    CROW_ROUTE(app, "/users/all")
            .methods(crow::HTTPMethod::GET)
                    ([](const crow::request &req){
                        // db logic
                        Database db("../core/app.db");
                        int count = db.countAllUsers();

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Users count retrieved successfully"},
                                                       {"count", count}
                                               });

                        return crow::response(200, res);
                    });

    // Pets logic

    // Add a pet
    CROW_ROUTE(app, "/pet/add")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request &req){
                        auto json_payload = crow::json::load(req.body);

                        if (!json_payload){
                            return crow::response(400, "Invalid JSON");
                        }

                        std::string name = json_payload["name"].s();
                        int age = json_payload["age"].i();
                        std::string type = json_payload["type"].s();
                        std::string genre = json_payload["genre"].s();
                        int userID = json_payload["userID"].i();

                        // db logic
                        Database db("../core/app.db");
                        bool status = db.insertPet(name, age, type, genre, userID);

                        if (!status){
                            return crow::response(500, "Internal Server Error");
                        }
                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Pet added successfully"}
                                               });

                        return crow::response(200, res);
                    });

    // Count pets by user
    CROW_ROUTE(app, "/pet/count")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request &req){
                        auto json_payload = crow::json::load(req.body);

                        if (!json_payload){
                            return crow::response(400, "Invalid JSON");
                        }

                        int userID = json_payload["userID"].i();

                        // db logic
                        Database db("../core/app.db");
                        int count = db.countPetByUser(userID);

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Pet count retrieved successfully"},
                                                       {"count", count}
                                               });

                        return crow::response(200, res);
                    });

    // Get pets info by user
    CROW_ROUTE(app, "/pet/get")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request &req){
                        auto json_payload = crow::json::load(req.body);

                        if (!json_payload){
                            return crow::response(400, "Invalid JSON");
                        }

                        int userID = json_payload["userID"].i();

                        // db logic
                        Database db("../core/app.db");
                        std::vector<Pet> pets = db.getPetsByUser(userID);

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Pets retrieved successfully"}
                                               });

                        // Create a JSON array for pets
                        std::vector<crow::json::wvalue> petsArray;
                        for (const auto& pet : pets) {
                            crow::json::wvalue petJson;
                            petJson["petID"] = pet.petID;
                            petJson["name"] = pet.name;
                            petJson["age"] = pet.age;
                            petJson["type"] = pet.type;
                            petJson["genre"] = pet.genre;
                            petsArray.emplace_back(petJson);
                        }
                        res["pets"] = std::move(petsArray); // Move the vector into the response

                        return crow::response(200, res);
                    });

    // Delete a pet
    CROW_ROUTE(app, "/pet/delete")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request &req){
                        auto json_payload = crow::json::load(req.body);

                        if (!json_payload){
                            return crow::response(400, "Invalid JSON");
                        }

                        int petID = json_payload["petID"].i();

                        // db logic
                        Database db("../core/app.db");
                        bool status = db.deletePet(petID);

                        if (!status){
                            return crow::response(500, "Internal Server Error");
                        }

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Pet deleted successfully"}
                                               });

                        return crow::response(200, res);
                    });

    // get all pets info and count
    CROW_ROUTE(app, "/pet/all")
            .methods(crow::HTTPMethod::GET)
                    ([](const crow::request &req){
                        // db logic
                        Database db("../core/app.db");
                        std::vector<Pet> pets = db.getPets();
                        // count all pets
                        int count = db.countAllPets();

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Pets retrieved successfully"}
                                               });

                        // Create a JSON array for pets
                        std::vector<crow::json::wvalue> petsArray;
                        for (const auto& pet : pets) {
                            crow::json::wvalue petJson;
                            petJson["petID"] = pet.petID;
                            petJson["name"] = pet.name;
                            petJson["age"] = pet.age;
                            petJson["type"] = pet.type;
                            petJson["genre"] = pet.genre;
                            petsArray.emplace_back(petJson);
                        }
                        res["pets"] = std::move(petsArray);
                        res["count"] = count;

                        return crow::response(200, res);
                    });

    // Appointments logic

    CROW_ROUTE(app, "/appointment/hours")
            .methods( crow::HTTPMethod::POST)
                    ([](const crow::request& req){
                        // Parse JSON request body
                        auto json = crow::json::load(req.body);
                        if (!json) {
                            return crow::response(400, "Bad Request");
                        }
                        // Get users date
                        std::string date = json["date"].s();

                        // Get available hours for today considering booked appointments
                        std::vector<std::string> availableHoursForToday = Citas::getAvailableHoursForToday(date, bookedHours);

                        // Construct JSON response
                        crow::json::wvalue res;
                        res["status"] = "success";
                        res["msg"] = "Available hours for today";

                        // Create a JSON array for hours
                        std::vector<crow::json::wvalue> hoursArray;
                        for (const auto& hour : availableHoursForToday) {
                            hoursArray.emplace_back(hour);
                        }
                        res["hours"] = std::move(hoursArray); // Move the vector into the response

                        return crow::response(200, res);
                    });

    CROW_ROUTE(app, "/appointment/create")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request& req){
                        // Parse JSON request body
                        auto json = crow::json::load(req.body);
                        if (!json) {
                            return crow::response(400, "Bad Request");
                        }

                        // Extract appointment details from JSON
                        std::string hour = json["hour"].s();
                        std::string date = json["date"].s();
                        std::string petName = json["petName"].s();
                        std::string phone = json["phone"].s();
                        std::string email = json["email"].s();
                        std::string ownerName = json["ownerName"].s();
                        std::string service = json["service"].s();

                        // Check if the selected hour is available
                        std::string selectedHour = date + " " + hour;

                        // Check if the selected hour is available
                        if (bookedHours.find(selectedHour) != bookedHours.end()) {
                            return crow::response(400, "Hour already booked");
                        }

                        // Book the appointment
                        bookedHours.insert(selectedHour);

                        //  Book the appointment into db
                        Database db("../core/app.db");
                        bool status = db.insertAppointment(petName, date, hour, service, email, phone, ownerName);

                        if (!status){
                            return crow::response(500, "Internal Server Error");
                        }

                        // Store the appointment details in a database or perform any other necessary actions
                        crow::json::wvalue res({
                                                       {"status", "OK"},
                                                       {"msg", "Appointment created successfully"}
                                               });

                        // Respond with success message
                        return crow::response(200,res);
                    });
    // Get count appointments by user
    CROW_ROUTE(app, "/appointment/count")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request &req){
                        auto json_payload = crow::json::load(req.body);

                        if (!json_payload){
                            return crow::response(400, "Invalid JSON");
                        }

                        std::string mail = json_payload["mail"].s();

                        // db logic
                        Database db("../core/app.db");
                        int count = db.countAppointmentsByUser(mail);

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Appointments count retrieved successfully"},
                                                       {"count", count}
                                               });

                        return crow::response(200, res);
                    });

    // Get all appointments and count
    CROW_ROUTE(app, "/appointment/all")
            .methods(crow::HTTPMethod::GET)
                    ([](const crow::request &req){

                        // db logic
                        Database db("../core/app.db");
                        std::vector<Cita> appointments = db.getAppointments();
                        // count all appointments
                        int count = db.countAllAppointments();
                        int done = db.countAllAppointmentsDone();

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Appointments retrieved successfully"}
                                               });

                        // Create a JSON array for appointments
                        std::vector<crow::json::wvalue> appointmentsArray;
                        for (const auto& appointment : appointments) {
                            crow::json::wvalue appointmentJson;
                            appointmentJson["AppointmentID"] = appointment.AppointmentID;
                            appointmentJson["PetName"] = appointment.PetName;
                            appointmentJson["AppointmentDate"] = appointment.AppointmentDate;
                            appointmentJson["AppointmentTime"] = appointment.AppointmentTime;
                            appointmentJson["Phone"] = appointment.Phone;
                            appointmentJson["Service"] = appointment.Service;
                            appointmentJson["OwnerName"] = appointment.OwnerName;
                            appointmentJson["Status"] = appointment.Status;
                            appointmentsArray.emplace_back(appointmentJson);
                        }
                        res["appointments"] = std::move(appointmentsArray);
                        res["count"] = count;
                        res["done"] = done;

                        return crow::response(200, res);
                    });

    // complete appointment
    CROW_ROUTE(app, "/appointment/complete")
            .methods(crow::HTTPMethod::POST)
                    ([](const crow::request &req){
                        auto json_payload = crow::json::load(req.body);

                        if (!json_payload){
                            return crow::response(400, "Invalid JSON");
                        }

                        int appointmentID = json_payload["appointmentID"].i();

                        // db logic
                        Database db("../core/app.db");
                        bool status = db.updateAppointmentStatus(appointmentID);

                        if (!status){
                            return crow::response(500, "Internal Server Error");
                        }

                        crow::json::wvalue res({
                                                       // return success message
                                                       {"status", "success"},
                                                       {"msg", "Appointment completed successfully"}
                                               });

                        return crow::response(200, res);
                    });


    app.bindaddr("127.0.0.1").port(18080).multithreaded().run();
}
