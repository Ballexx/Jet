#pragma once

class Request{
    public:
    char* method;
    char* protocol;
    char* path;
    char* body;
    Request();
    void read_request(char* data, int buflen);
};