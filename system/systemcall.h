#ifndef _SYSTEM_CALL_H_
#define _SYSTEM_CALL_H_
#include <stdarg.h>

#define _SYS_CALL_(ID) asm("svc #"_SYS_CALL_NO_(ID))
#define _SYS_CALL_NO_(num) #num
void system_call(int);
#endif