//
// Created by zaiyangli on 4/22/16.
//

#ifndef _PATH_H
#define _PATH_H

#include "../libc/string.h"
#define PATH_MAXIMUM_LEVEL 16

void parse_path(char* path, char** parts, int n, int* parts_count);
void path_get_file_name(char* path,  char* buffer, int length);


#endif //_PATH_H
