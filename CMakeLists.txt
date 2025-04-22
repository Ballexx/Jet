cmake_minimum_required(VERSION 4.0.1)
project(jet)
target_include_directories(jet PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(jet src/main.cpp src/helper.cpp src/request.cpp src/response.cpp src/router.cpp src/server.cpp)