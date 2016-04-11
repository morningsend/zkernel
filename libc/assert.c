//
// Created by zaiyangli on 4/9/16.
//

#include "assert.h"
#include "io.h"

void __assert(char* message, char* file, int line ){
    printf("%s:%d Assertion failed: %s", file,line, message);
}