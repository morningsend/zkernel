//
// Created by zaiyangli on 4/20/16.
//

#include "shell.h"

#define IN_BUF_SIZE 127
char prompt_text[] = "$ ";

void execFork(char** options, int argc){

    if(argc < 2) printf("fork: usage\n\t fork [command]");
    int tid = fork();
    printf("fork executed. tid=%d", tid);
}

void command(char** options, int argc){
    if(argc < 1) return;
    char* prog_name = options[0];
    if(strcmp(prog_name, "P0") == 0){
        P0();
    }else if(strcmp(prog_name, "P1") == 0){
        P1();
    }else if(strcmp(prog_name, "P2") == 0){
        P2();
    }else if(strcmp(prog_name, "fork") == 0){
        execFork(options, argc);
    }else if(strcmp(prog_name, "exit") == 0){
        printf("\nShell Exit.");
        exit(0);
    }else {
        printf("command %s not found\n", prog_name);
    }
}


void parse_input(char* line, char** args, int n, int* argc){
    str_splt_ws(line, args, n, argc);
}

int shell_main(int argc, char **argv){
    char input_buffer[128];
    char* args_buf[32];
    int argn = 0;
    while(1){
        puts(prompt_text);
        gets(input_buffer, IN_BUF_SIZE);
        parse_input(input_buffer, args_buf,32 ,&argn);
        command(args_buf, argn);
    }
}