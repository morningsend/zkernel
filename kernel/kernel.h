#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "../device/device.h"
#include "process.h"
#include "../system/systemcall.h"
#include "sys_init.h"
#include "syscall_def.h"

void kernel_init(int* a);
extern void enable_irq_interrupt();
extern void disable_irq_interrupt();
extern void enable_fiq_interrupt();
extern void disable_fiq_interrupt();
void kernel_syscall_dispatch();
void kernel_main_loop();
void kernel_ready();

#endif