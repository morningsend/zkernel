//
// Created by zaiyangli on 4/20/16.
//

#include "shell.h"

#define IN_BUF_SIZE 255

static char current_dir[IN_BUF_SIZE] = "/";
static char input_buffer[IN_BUF_SIZE];
static char* args_buf[32];

void execFork(char** options, int argc){

    if(argc < 2){
        printf("fork: usage\n\t fork [command]\n");
        return;
    }
    int tid = fork();
    printf("fork executed. tid=%d", tid);
    if(tid == 0){
        command(&options[1], ++argc );
    }else {

    }
}
void execMkdir(char** options, int argc){
    if(argc != 2) {
        printf("mkdir\nusage:\t mkdir dirpath\n");
        return;
    }
    char path[128];
    char path2[128];
    strcpy(path, current_dir);
    path_resolve(path, options[1],path2);
    if(_fexists(path2))
        printf("Directiory/File with name %s already exists.\n", options[1]);
    else{
        path_resolve(path, options[1],path2);
        _mkdir(path2);
    }
}

void execCd(char **options, int argc){

    if(argc!=2) {
        printf("cd\nusage:\tcd path");
        return;
    }
    char path[128];
    char path2[128];
    strcpy(path, current_dir);
    path_resolve(path, options[1], path2);
    if(_dir_exists(path2)){
        path_resolve(current_dir, options[1], path2);
        strcpy(current_dir, path2);
    }else {
        printf("Directory %s does not exists.\n", options[1]);
    }
}
void execRun(char **options, int argc){

}
void execTouch(char **options, int argc){
    if(argc != 2)
    {
        printf("touch\nusage:\ttouch filepath\n");
        return;
    }
    char path[128];
    path_resolve(current_dir, options[1], path);
    if(_fexists(path)) return;

    path_resolve(current_dir, options[1], path);
    p_file fp = _fopen(path, FILE_WRITE_ONLY|FILE_CREATE);

    if(fp == NULL){
        printf("Could not create file ");
    }else{
        _fclose(fp);
        fp = NULL;
    }
}
void execRm(char **options, int argc){

}
void execLs(char* options, int argc){

}
void execDiskFormat(){
    disk_format();
    fs_init();
    strcpy(current_dir,"/");
    printf("Disk formatting complete\n");
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
    }else if(strcmp(prog_name, "multithread")== 0){

        printf("executing multithreading demo");
        runMultiThreadDemo();

    }else if(strcmp(prog_name, "mkdir")==0){

        execMkdir(options, argc);

    }else if(strcmp(prog_name, "run") == 0){

        execRun(options, argc);
    }else if(strcmp(prog_name, "touch")==0){

        execTouch(options, argc);
    }else if(strcmp(prog_name, "cd")==0){
        execCd(options, argc);
    }else if(strcmp(prog_name, "diskfmt")==0){
        execDiskFormat();
    }
    else {
        printf("command %s not found\n", prog_name);
    }
}


void parse_input(char* line, char** args, int n, int* argc){
    str_splt_ws(line, args, n, argc);
}
int shell_main(int argc, char **argv){
    int argn = 0;
    while(1){
        printf("%s $ ", current_dir);
        gets(input_buffer, IN_BUF_SIZE);
        parse_input(input_buffer, args_buf,32 ,&argn);
        command(args_buf, argn);
    }
}