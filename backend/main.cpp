#include "crow_all.h"

int main()
{
    // crow app with CORS handler
    
    
    crow::App<crow::CORSHandler> app;

    // Customize CORS
    auto& cors = app.get_middleware<crow::CORSHandler>();

    // clang-format off
    cors
      .global()
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
        .methods("POST"_method, "GET"_method)
        .origin("*");
    // clang-format on

    // hello
    CROW_ROUTE(app, "/api/hello").methods( "GET"_method)
    ([](){
        crow::json::wvalue res({{"message", "Hello, World!"}});
        return res;
    });
    // get avail hours 
    /*
    Each day has a different set of available hours, 8 houres per day from 8 AM to 16 PM

    
    */
    CROW_ROUTE(app, "/api/get/available/hours/date=<string>").methods("POST"_method, "GET"_method )
    ([](std::string date){
        if(date == "22-4-2024"){
            crow::json::wvalue res({{"error", "No available hours for this date"}});
            return res;
        } else {
            crow::json::wvalue res;
            res["date"] = date;
            res["hours"] = {"8:00","9:00","10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};
            return res;
        }
    });

    CROW_ROUTE(app, "/api/new/visit/<string>/<string>/<string>/<string>/<string>").methods("POST"_method)
    ([](std::string petName, std::string mail, std::string phone, std::string date, std::string hour){
        crow::json::wvalue res({{"petName", petName}, {"mail", mail},
        {"phone", phone}, {"date", date}, {"hour", hour}});
	    return res;
	});


    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}
