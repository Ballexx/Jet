#include <stdint.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.hpp"
#include <arpa/inet.h>
#include <cerrno>

using namespace std;

Server::Server(const char* host, uint16_t port){
    _host = host;
    _port = port;
}

const char* get_socket_creation_error(){
    switch(errno){
    case EAGAIN:
        return "Resource temporarily unavailable.";
    case EINVAL:
        return "The request is invalid or not supported.";
    case EIO:
        return "There has been a network or transport failure.";
    case ENOBUFS:
        return "Insufficient system resources are available to complete the call.";
    };
    return "Unknown error.";
}

const char* get_socket_binding_error(){
    switch(errno){
    case EPERM:
        return "The user is not authorized to bind to the port specified.";
    case ENOBUFS:
        return "Bind is unable to obtain a buffer due to insufficient storage.";
    case EACCES:
        return "Permission denied.";
    case EADDRINUSE:
        return "The address is already in use.";
    };
    return "Unknown error.";
}

void handle_request(int socket, int buffer_size){
    char buffer[buffer_size];
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof (client_addr);

    int bytes = recvfrom(socket, buffer, buffer_size, 0, (struct sockaddr*)&client_addr, &addr_len);

    sendto(socket, buffer, buffer_size, 0, (struct sockaddr*)&client_addr, addr_len);
}

void Server::run(){
    if(max_buffer_size > 16000){
        cout << "Large buffer size, consider lowering it." << endl;
    }
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == -1){
        cout << "Socket failed creation with errorcode: " << endl;
        cout << get_socket_creation_error() << endl;
        cout << "Terminating gracefully..." << endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY; //This must be fixed later
    socket_address.sin_port = htons(_port);

    int _bind = bind(sock, (struct sockaddr*)&socket_address, sizeof(socket_address));

    if(_bind == -1 ){
        cout << "Socket not able to be bound to port with errorcode: " << endl;
        cout << get_socket_binding_error() << endl;
        cout << "Terminating gracefully..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Socket bound to port " << _port << endl;

    while(true){
        handle_request(sock, max_buffer_size);
    }
}