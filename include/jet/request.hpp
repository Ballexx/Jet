#pragma once
#include "utils/common.hpp"

class Request{
    public:
    void parse(std::string request_data);

    std::string method;
    std::string target;
    std::string version;
    std::string body;

    std::vector<std::string> headers;

    const std::string& get_method() const{ return method; }
    const std::string& get_target() const{ return target; }
    const std::string& get_version() const{ return version; }
    const std::string& get_body() const{ return body; }

    const std::vector<std::string>& get_headers() const { return headers; }

    private:
    void set_method(const std::string& _method){ method = _method; }
    void set_target(const std::string& _target){ target = _target; }
    void set_version(const std::string& _version){ version = _version; }
    void set_body(const std::string& _body){ body = _body; }
    
    void set_headers(const std::vector<std::string>& _headers){ headers = _headers; }
};