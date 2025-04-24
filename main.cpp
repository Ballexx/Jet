#include "jet.hpp"
#include <iostream>
using json = nlohmann::json;

void send_body(Request& req, Response& res){
    res.send("Hello!");
}

void send_json(Request& req, Response& res){
    json data = json::parse(R"(
        {
          "pi": 3.141,
          "dogs": true
        }
      )");
    
    res.send_json(data);
}

void send_hi(Request& req, Response& res){
    std::cout << "Hi!" << std::endl;
}

int main(){
    Server server("127.0.0.1", 3000);
    Router& router = Router::get();

    router.mount("GET", "/", send_body);
    router.mount("GET", "/json", send_json);

    router.mount("POST", "/", send_hi);    

    server.fire();

    return 0;
}