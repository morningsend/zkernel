#ifndef _SYSTEM_CALL_H_
#define _SYSTEM_CALL_H_

#ifndef NULL
#define NULL ((void *)0)
#endif

#define _SYS_CALL_(ID) asm("mov r7, %[sysnum]\n"\
                            "svc #0\n"\
                            ::[sysnum] "r" (ID):"r7");

#define _SYS_CALL_ARG_1(ID, arg1) asm("mov r0, %[a]\n"\
                                "mov r7, %[sysnum]\n"\
                                "svc #0"\
                                ::[sysnum] "r" (ID),[a] "r" (arg1)\
                                :"r0", "r1"\
);

#define _SYS_CALL_ARG_2(ID, arg1, arg2) asm("mov r0, %[a]\n"\
                                "mov r1, %[b]\n"\
                                "mov r7, %[sysnum]\n"\
                                "svc #0\n"\
                                ::[sysnum] "r" (ID),[a] "r" (arg1),[b] "r" (arg2)\
                                :"r0", "r1", "r2"\
);

#define _SYS_CALL_ARG_3(ID, arg1, arg2, arg3) asm("mov r0, %[a]\n"\
                                "mov r1, %[b]\n"\
                                "mov r2, %[c]\n"\
                                "mov r7, %[sysnum]\n"\
                                "svc #0"\
                                ::[sysnum] "r" (ID),[a] "r" (arg1),[b] "r" (arg2), [c] "r" (arg3)\
                                :"r0", "r1", "r2", "r3"\
);

#define _SYS_CALL_GET_NUMBER(sysno) asm volatile("mov %[id], r7\n":[id] "=r" (sysno)::);
#endif