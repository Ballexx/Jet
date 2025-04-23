cmake_minimum_required(VERSION 3.10)
project(jet)

add_library(jet 
    src/helper.cpp 
    src/request.cpp 
    src/response.cpp 
    src/router.cpp 
    src/server.cpp
)

add_executable(jet_app app/main.cpp)

target_include_directories(jet PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(jet_app PRIVATE jet)