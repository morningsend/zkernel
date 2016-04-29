//
// Created by zaiyangli on 4/29/16.
//

#include "demo.h"
#include "../kernel/syscall_def.h"



void runMultiThreadDemo(){
    int id = SYSCALL_RunMultiThreadDemo;
    _SYS_CALL_(id);
}