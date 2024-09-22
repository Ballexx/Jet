#include "server.hpp"

int main(){
    Server server("127.0.0.1", 3000);
    server.run();

    return 0;
}