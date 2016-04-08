#include "systemcall.h"

int system_call(int sys_call_number, ...){

    asm volatile("svc #0");
    return 0;
}

