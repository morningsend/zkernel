//
// Created by zaiyangli on 4/10/16.
//

#include "context.h"
#include "../libc/string.h"


void init_context(context* con){
    memset(con, sizeof(context),0);
}

void context_clone(context* con1, context* cont2){

}

void context_save_to_stack(context* con , uint32_t word){
    con->stackPointer -= sizeof(uint32_t);
    *(uint32_t*) con->stackPointer = word;
}