#pragma once
#include <stdint.h>

class Server{
    public:
    Server(const char* host, uint16_t port);
    
    int fire();

    private:
    const char* host;
    int port;
};