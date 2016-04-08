#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "device.h"

#include "systemcall.h"


void kernel_init(int* a);
extern void enable_irq_interrupt();
extern void disable_irq_interrupt();
extern void enable_fiq_interrupt();
extern void disable_fiq_interrupt();
#endif