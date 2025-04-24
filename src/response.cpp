#include "jet/response.hpp"
#include "third_party/json.hpp"
#include <map>

#include <string>
using json = nlohmann::json;

std::string Response::format(){
    std::string compiled_header = compile_header();
    std::string status_line = "HTTP/1.1 " + std::to_string(status) + "\r\n";
    std::string content_length = "Content-Length: " + std::to_string(body.size()) + "\r\n";
    std::string header = compiled_header;

    return status_line + content_length + compiled_header + "\r\n" + body;
}

std::string Response::compile_header(){
    std::string compiled_header;

    for(int i = 0; i < uncompiled_header.size(); i++){
        std::string key;
        std::string value;

        for(std::map<std::string, std::string>::iterator it = uncompiled_header[i].begin(); it != uncompiled_header[i].end(); it++){
            key = it->first;
            value = it->second;
        }
        std::string header;

        if(i != uncompiled_header.size()){
            header = key + ": " + value + "\r\n";
        }
        else{
            header = key + ": " + value;
        }
        compiled_header += header;
    }
    return compiled_header;
}

void Response::append_header(std::string key, std::string value){
    for(int i = 0; i < uncompiled_header.size(); i++){
        std::string _key;

        for(std::map<std::string, std::string>::iterator it = uncompiled_header[i].begin(); it != uncompiled_header[i].end(); it++){
            _key = it->first;
        }
        if(key == _key){
            uncompiled_header[i][key] = value;
            return;
        }
        else{
            continue;
        }
    }
    
    std::map<std::string, std::string> header;
    header[key] = value;
    uncompiled_header.push_back(header);
}

void Response::send(std::string body){
    set_body(body);
}

void Response::send_json(json body){
    std::string str_body = body.dump();
    append_header("Content-Type", "application/JSON");
    set_body(str_body);
}

