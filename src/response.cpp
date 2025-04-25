#include "jet/response.hpp"
#include "third_party/json.hpp"
#include "jet/helper.hpp"
#include "jet/config.hpp"

#include <map>

#include <string>
using json = nlohmann::json;

void Response::handle_server_error(){

}

std::string Response::format(){
    std::string compiled_header = compile_header();
    std::string status_line = "HTTP/1.1 " + std::to_string(status) + "\r\n";
    std::string content_length = "Content-Length: " + std::to_string(body.size()) + "\r\n";
    std::string header = compiled_header;

    return status_line + content_length + compiled_header + "\r\n" + body;
}

void handle_GET(){

}
void handle_POST(){

}
void handle_PUT(){

}
void handle_PATCH(){

}
void handle_DELETE(){

}
void handle_OPTIONS(){

}
void handle_HEAD(){

}
void handle_CONNECT(){

}
void handle_TRACE(){

}

std::string Response::handle_method(std::string method_type){
    http_method method = string_to_method(method_type);

    switch (method) {
        case http_method::GET:      handle_GET(); break;
        case http_method::POST:     handle_POST(); break;
        case http_method::PUT:      handle_PUT(); break;
        case http_method::PATCH:    handle_PATCH(); break;
        case http_method::DELETE_:  handle_DELETE(); break;
        case http_method::HEAD:     handle_HEAD(); break;
        case http_method::OPTIONS:  handle_OPTIONS(); break;
        case http_method::CONNECT:  handle_CONNECT(); break;
        case http_method::TRACE:    handle_TRACE(); break;
        default: handle_server_error(); break;
    }

    return format();
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

void Response::send_html(std::string path){
    std::string file_content = read_file(path);
    set_body(file_content);
}
