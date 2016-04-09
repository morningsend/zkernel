//
// Created by zaiyangli on 4/7/16.
//

#ifndef _PROCESS_H
#define _PROCESS_H



#define PROCESS_NEW 0
#define PROCESS_RUNNING 1
#define PROCESS_WAITING 2
#define PROCESS_TERMINATED -1



struct process_struct{
    int pid;
    int exit_code;
    int status;
};

int createProcess(void(*task)());
void killProcess(int pid);
void pauseProcess(int pid);
void runProcess(int pid);

#endif //_PROCESS_H
