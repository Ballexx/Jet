#include "jet/response.hpp"
#include "third_party/json.hpp"
#include <map>

#include <string>
using json = nlohmann::json;

std::string Response::format(){
    std::string compiled_header = compile_header();
    std::string status_line = "HTTP/1.1 " + std::to_string(status) + "\r\n";
    std::string body_header = "Content-Length: " + std::to_string(body.size()) + "\r\n";
    std::string body = "";
    
    return status_line + body_header + "\r\n" + body;
}

std::string Response::compile_header(){
    std::string compiled_header;

    for(int i = 0; i < uncompiled_header.size(); i++){
        for(std::map<std::string, std::string>::iterator it = uncompiled_header[i].begin(); it != uncompiled_header[i].end(); it++){
            std::string key = it->first;
            std::string value = it->second;
            std::string header = key + ": " + value + "\r\n";
                
            compiled_header += header;
        }
    }

    return compiled_header;
}

void Response::append_header(std::string key, std::string value){
    std::map<std::string, std::string> header;
    header[key] = value;
    uncompiled_header.push_back(header);
}

void Response::send(std::string body){
    set_body(body);
}

void Response::send_json(json body){
    set_body(body);
}

