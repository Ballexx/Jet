#include "jet/response.hpp"
#include "third_party/json.hpp"

#include <string>
using json = nlohmann::json;

void Response::send(std::string body){
    set_body(body);
}

void Response::send_json(json body){
    set_body(body);
}

