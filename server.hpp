#include <stdint.h>
#pragma once

class Server{
    public:
    Server(const char* host, uint16_t port);
    int run();

    uint16_t max_buffer_size = 8192;

    private:
    const char* _host;
    uint16_t _port;
    
};