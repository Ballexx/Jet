#include <stdint.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.hpp"
#include "request.hpp"
#include <arpa/inet.h>
#include <string.h>
#include <cerrno>

using namespace std;

Server::Server(const char* host, uint16_t port){
    _host = host;
    _port = port;
}

void handle_request(int server_socket, int buffer_size){
    char buffer[buffer_size];
    sockaddr_in client_addr;
    socklen_t addr_len = sizeof (client_addr);

    int client_socket = accept(server_socket, (sockaddr*)&client_addr, &addr_len);
    uint16_t data = recv(client_socket, &buffer, (buffer_size - 1), 0);

    Request request;
    request.read_request(buffer, data);

    
}

int Server::run(){
    if(max_buffer_size > 16384){
        cout << "Large buffer size, consider lowering it." << endl;
    }
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == -1){
        cout << "Socket failed creation with error: " << strerror(errno) << " Terminating..." << endl;
        return -1;
    }

    int option_name = SO_REUSEADDR;
    int option_val = 1;
    int sock_options = setsockopt(sock, SOL_SOCKET, option_name, &option_val, sizeof(int));

    if(sock_options == -1){
        cout << "Socketoptions failed to configure with error: " << strerror(errno) << " Terminating..." <<endl;
        return -1;
    }

    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY; //This must be fixed later
    socket_address.sin_port = htons(_port);

    int _bind = bind(sock, (struct sockaddr*)&socket_address, sizeof(socket_address));

    if(_bind == -1 ){
        cout << "Socket failed to bind with error: " << strerror(errno) << " Terminating..."<< endl;
        return -1;
    }

    if(listen(sock, 1) == -1){
        cout << "Not able to listen to port with error: " << strerror(errno) << " Terminating..."<< endl;
        return -1;
    }

    cout << "Server listening on port " << _port << endl;

    while(true){
        handle_request(sock, max_buffer_size);
    }
}