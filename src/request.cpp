#include "utils/common.hpp"

#include "jet/request.hpp"
#include "jet/helper.hpp"

// Parses request header
// Param is raw requestdata as a string

void Request::parse(std::string request_data){
    size_t header_end = request_data.find("\r\n\r\n");

    std::string raw_headers = request_data.substr(0, header_end);
    std::string body = request_data.substr(header_end + 4);

    std::vector<std::string> headers = split(raw_headers, "\r\n");

    std::string request_line_str = headers[0];
    std::vector<std::string> request_line = split(request_line_str, " ");
    
    set_method(request_line[0]);
    set_target(request_line[1]);
    set_version(request_line[2]);
    set_body(body);
    
    headers.erase(headers.begin());

    set_headers(headers);
}