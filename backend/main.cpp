#include "crow_all.h"

int main()
{
    // crow app
    crow::SimpleApp app; 
    
    // routes 

    // hello world route 
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    // get avail hours 
    CROW_ROUTE(app, "/api/get/available/hours/date=<string>").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)
    ([](std::string date){
        crow::json::wvalue res;
        res["date"] = date;
        res["hours"] = {"10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};
        return res;
    });

    CROW_ROUTE(app, "/api/new/visit/petName=<string>&mail=<string>&phone=<string>&date=<string>&hour=<string>").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)
    ([](std::string petName, std::string mail, std::string phone, std::string date, std::string hour){
        crow::json::wvalue res({{"petName", petName}, {"mail", mail},
        {"phone", phone}, {"date", date}, {"hour", hour}});
	    return res;
	});


    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}
