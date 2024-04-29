#include "crow_all.h"
#include "sqlite3.h"
#include <chrono>
#include <ctime>
#include <unordered_set> // For efficient lookup of selected hours
#include <vector>
#include <string>

// import libraries for auth
#include "spark/spark.cpp"

// import libraries for database
#include "core/Database.cpp"

// Custom utils library
#include "utils/AvailHours.cpp"

int main()
{
    // crow app with CORS handler
    crow::App<crow::CORSHandler> app;

    // Customize CORS
    auto& cors = app.get_middleware<crow::CORSHandler>();

    // cors config
    cors
    .global()
            .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
            .methods("POST"_method, "GET"_method)
            .origin("*");
    // clang-format on

    // route for check if server works
    // /health
    CROW_ROUTE(app, "/health").methods("GET"_method)
    ([]() {
        return crow::response(200, "OK");
    });

    // classic route for hello world
    // /hello
    CROW_ROUTE(app, "/hello").methods("GET"_method)
    ([]() {
        return crow::response(200, "Hello, World!");
    });

    // routes for auth system
    // route for register new user
    // /api/auth/register
    CROW_ROUTE(app, "/api/auth/register")
    .methods("POST"_method)
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


    CROW_ROUTE(app, "/api/auth/login")
    .methods("POST"_method)
    ([](const crow::request &req){
        
        auto json_payload = crow::json::load(req.body);

        if (!json_payload){
            return crow::response(400, "Invalid JSON");
        }

        std::string user = json_payload["user"].s();
        std::string password = json_payload["password"].s();

        // auth logic
        Database db("../core/app.db");
        bool isLogged = db.loginUser(user, password);

        if (!isLogged){
            return crow::response(401, "Unauthorized");
        }
        // generate a JWT token
        std::string token = db.getUserToken(user);

        crow::json::wvalue res({
            {"status", "success"},
            {"msg", "User logged in successfully"},
            {"token", token}
        });

        return crow::response(200, res);
    });

    // route for get available hours for the appointment
    CROW_ROUTE(app, "/api/appointment/hours")
    .methods("GET"_method)
    ([](){
        // Get available hours for today considering booked appointments
        std::vector<std::string> availableHoursForToday = getAvailableHoursForToday();

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
    // route for create a new appointment for a pet in the system
    // Endpoint to handle appointment creation
    CROW_ROUTE(app, "/api/appointment/create")
            .methods("POST"_method)
                    ([](const crow::request& req){
                        // Parse JSON request body
                        auto json = crow::json::load(req.body);
                        if (!json) {
                            return crow::response(400, "Bad Request");
                        }

                        // Extract appointment details from JSON
                        std::string selectedHour = json["hour"].s();
                        std::string selectedDate = json["date"].s();
                        std::string petName = json["petName"].s();
                        std::string phone = json["phone"].s();
                        std::string email = json["email"].s();

                        // Check if the selected hour is available
                        if (bookedHours.find(selectedHour) != bookedHours.end()) {
                            return crow::response(400, "Hour already booked");
                        }

                        // Book the appointment
                        bookedHours.insert(selectedHour);

                        // Store the appointment details in a database or perform any other necessary actions
                        crow::json::wvalue res({
                            {"status", "OK"},
                            {"msg", "Appointment created successfully"}
                        });

                        // Respond with success message
                        return crow::response(200,res);
                    });





    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}
