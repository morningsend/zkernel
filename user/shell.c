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

char* skip_ws(char* string){
    int done = 0;
    while(*string !='\0' && !done){
        switch(*string){
            case ' ':
            case '\n':
            case '\r':
            case '\t':
            case '\f':
                *string = '\0';
                string++;
                break;
            default:
                done = 1;
                break;
        }
    }
    return string;
}
char* skip_non_ws(char* string){
    int done = 0;
    while(*string !='\0' && !done){
        switch(*string){
            case ' ':
            case '\n':
            case '\r':
            case '\t':
            case '\f':
                done = 1;
                break;
            default:
                string++;
                break;
        }
    }
    return string;
}
void parse_input(char* line, char** args, int* argc){
    char* c = line;
    int count = 0;
    do {
        c = skip_ws(c);
        if(*c != '\0'){
            *args = c;
            count++;
            args++;
            c = skip_non_ws(c);
        }
    }while(* c != '\0');

    *argc = count;
}

int shell_main(int argc, char **argv){
    char input_buffer[128];
    char* args_buf[32];
    int argn = 0;
    while(1){
        puts(prompt_text);
        gets(input_buffer, IN_BUF_SIZE);
        parse_input(input_buffer, args_buf, &argn);
        command(args_buf, argn);
    }
}