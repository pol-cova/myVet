#include "crow_all.h"

int main()
{
    crow::SimpleApp app; //define your crow application

    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    CROW_ROUTE(app, "/json")
    ([]{
    crow::json::wvalue x({{"message", "Hello, World!"}});
    return x;
    });

    CROW_ROUTE(app, "/new/visit/petName=<string>&mail=<string>&phone=<string>&date=<string>&hour=<string>").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)
    ([](std::string petName, std::string mail, std::string phone, std::string date, std::string hour){
     	crow::json::wvalue res({{"petName", petName}, {"mail", mail},
                               {"phone", phone}, {"date", date}, {"hour", hour}});
	return res;
	});


    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}
