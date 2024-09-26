#include "request.hpp"
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

using namespace std;

Request::Request(){
    char* method;
    char* path;
    char* protocol;
    char* body;
}

void read_general_headers(char* field){
    for(int i = 0; i < 256; i++){
        cout << field[i] << flush;
    }
}

void Request::read_request(char* data, int buflen){    
    char line[255];
    uint8_t line_index = 0;

    if(method == NULL){
        cout << "test";
    }

    for(int i = 0; i < buflen; i++){
        if(data[i] == 0x0A){
            memset(line, 0, sizeof(line));
            line_index = 0;
            continue;
        }
        
        if(data[i] == 0x0D){
            if(method == ""){
                read_general_headers(line);
            }
        }
        line[line_index] = data[i];
        line_index += 1;
    }
}