#pragma once
#include <string>
#include <vector>
#include <map>
#include "third_party/json.hpp"
using json = nlohmann::json;

class Response{
    public:
    std::string handle_method(std::string method_type);
    std::string format();

    void Response::handle_server_error();

    void set_status(int _status) { status = _status; }
    void set_body(const std::string& _body) { body = _body; }

    void send(std::string body);
    void send_json(json body);
    void send_html(std::string path);

    void append_header(std::string key, std::string value);

    private:
    std::string compile_header();

    uint16_t status = 200;
    std::string body;
    std::vector<std::map<std::string, std::string>> uncompiled_header;
};