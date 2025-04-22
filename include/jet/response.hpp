#pragma once
#include <string>
#include "third_party/json.hpp"
using json = nlohmann::json;

class Response{
    public:
    std::string format() const {
        std::string status_line = "HTTP/1.1 " + std::to_string(status) + "\r\n";
        std::string body_header = "Content-Length: " + std::to_string(body.size()) + "\r\n";
        return status_line + body_header + "\r\n" + body;
    }

    void set_status(int _status) { status = _status; }

    void send(std::string body);
    void send_json(json body);

    private:
    void set_body(const std::string& _body) { body = _body; }

    int status = 200;
    std::string body;
};