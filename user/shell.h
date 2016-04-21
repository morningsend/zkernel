//
// Created by zaiyangli on 4/20/16.
//

#ifndef _SHELL_H
#define _SHELL_H

#include "../libc/io.h"
#include "P0.h"
#include "P1.h"
#include "P2.h"
#include "../system/syslib.h"
int shell_main(int argc, char* argv[]);
void command(char** options, int argc);
void parse_input(char* line, char** args, int* argc);

#endif //_SHELL_H
