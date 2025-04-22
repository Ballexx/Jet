#include "utils/common.hpp"

#include "jet/server.hpp"
#include "jet/request.hpp"
#include "jet/response.hpp"
#include "jet/router.hpp"

//For MinGW link -lws2_32

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")

    typedef SOCKET socket_t;
    #define CLOSESOCKET closesocket
    #define GET_ERROR WSAGetLastError()
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    typedef int socket_t;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR   -1
    #define CLOSESOCKET close
    #define GET_ERROR errno
#endif

int init_sockets() {
#ifdef _WIN32
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
#else
    return 0;
#endif
}

void cleanup_sockets() {
#ifdef _WIN32
    WSACleanup();
#endif
}

Server::Server(const char* _host, uint16_t _port) : host(_host), port(_port){}

const uint16_t max_buffer_size = 8192;

int Server::fire(){
    if (init_sockets() != 0) {
        std::cerr << "Socket init failed!" << std::endl;
        return 1;
    }

    socket_t server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << GET_ERROR << std::endl;
        cleanup_sockets();
        return 1;
    }

    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY; //This must be fixed later
    socket_address.sin_port = htons(port);

    int bind_socket = bind(server_socket, (struct sockaddr*)&socket_address, sizeof(socket_address));

    if(bind_socket == SOCKET_ERROR){
        std::cout << "Socket failed to bind with error: " << GET_ERROR << " Terminating..."<< std::endl;
        CLOSESOCKET(server_socket);
        cleanup_sockets();
        return 1;
    }

    if(listen(server_socket, 1) == SOCKET_ERROR){
        std::cout << "Not able to listen to port with error: " << GET_ERROR << " Terminating..."<< std::endl;
        CLOSESOCKET(server_socket);
        cleanup_sockets();
        return 1;
    }

    std::cout << "Server listening on port " << port << std::endl;

    while(true){
        char buffer[max_buffer_size];
        sockaddr_in client_addr;
        socklen_t addr_len = sizeof (client_addr);
    
        int client_socket = accept(server_socket, (sockaddr*)&client_addr, &addr_len);
        uint16_t bytes_read = recv(client_socket, buffer, (max_buffer_size - 1), 0);
        buffer[bytes_read] = '\0';
        std::string request_data = buffer;

        Request request;
        request.parse(request_data);

        Response response;

        Router::get().execute(request, response);

        std::string response_str = response.format();
        send(client_socket, response_str.c_str(), response_str.size(), 0);
        
    }

    CLOSESOCKET(server_socket);
    cleanup_sockets();

    return 0;
}