//
// Created by zaiyangli on 4/20/16.
//

#include "util.h"


/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long x[N];      /* the array for the state vector  */
static unsigned long *p0, *p1, *pm;

void init_genrand(unsigned long s)
{
    int i;

    x[0] = s & 0xffffffffUL;
    for (i = 1; i < N; ++i) {
        x[i] = (1812433253UL * (x[i - 1] ^ (x[i - 1] >> 30)) + i)
               & 0xffffffffUL;           /* for >32 bit machines */
    }
    p0 = x;
    p1 = x + 1;
    pm = x + M;
}

/* generates a random number on the interval [0,0xffffffff] */
unsigned long genrand_int32(void)
{
    unsigned long y;

    if (!p0) {
        /* Default seed */
        init_genrand(5489UL);
    }
    /* Twisted feedback */
    y = *p0 = *pm++ ^ (((*p0 & UPPER_MASK) | (*p1 & LOWER_MASK)) >> 1)
              ^ (-(*p1 & 1) & MATRIX_A);
    p0 = p1++;
    if (pm == x + N) {
        pm = x;
    }
    if (p1 == x + N) {
        p1 = x;
    }
    /* Temper */
    y ^= y >> 11;
    y ^= y << 7 & 0x9d2c5680UL;
    y ^= y << 15 & 0xefc60000UL;
    y ^= y >> 18;
    return y;
}

/* generates a random number on the interval [0,0x7fffffff] */
long genrand_int31(void)
{
    return (long) (genrand_int32() >> 1);
}