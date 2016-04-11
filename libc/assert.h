//
// Created by zaiyangli on 4/9/16.
//

#ifndef _ASSERT_H
#define _ASSERT_H


#if defined(NODEBUG)
#define assert(condition)
#else
#define assert(condition) if (!condition) \
{\
__assert (#condition, __FILE__, __LINE__);\
}

void __assert(char* messenger, char* file, int line );
#endif
#endif //_ASSERT_H
