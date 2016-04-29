//
// Created by zaiyangli on 4/22/16.
//

#include "path.h"


void parse_path(char* path, char** parts, int n, int* parts_count){
    str_splt('/', path, parts, n, parts_count);
}
void path_get_file_name(char* path,  char* buffer, int length){

}
void path_resolve(char* parent_path, char* path, char* result){
    int len = strlen(parent_path);
    if(path[0] == '/'){
        strcpy(result, path);
    }else {
        strcpy(result, parent_path);
        if (parent_path[len - 1] != '/') {
            result[len] = '/';
            strcpy(result + len + 1, path);
        }else{
            strcpy(result+len, path);
        }
    }
}