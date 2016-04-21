//
// Created by zaiyangli on 4/8/16.
//

#include "sys_init.h"


void system_init(){

}

void user_init(){
    _start();
}

void user_idle(){
    while(1){
        asm volatile("nop\n");
    }
}