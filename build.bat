@echo off
g++ -Iinclude main.cpp src/helper.cpp src/request.cpp src/response.cpp src/router.cpp src/server.cpp -o jet -lws2_32
