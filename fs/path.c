//
// Created by zaiyangli on 4/22/16.
//

#include "path.h"


void parse_path(char* path, char** parts, int n, int* parts_count){
    str_splt('/', path, parts, n, parts_count);
}

void path_get_file_name(char* path,  char* buffer, int length){

}