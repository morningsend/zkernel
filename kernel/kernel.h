#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "../device/device.h"
#include "process.h"
#include "../system/systemcall.h"
#include "sys_init.h"
#include "syscall_def.h"
#include "process.h"
#include "context.h"
#include "schedule.h"

void kernel_init();
void kernel_shutdown();
extern void enable_irq_interrupt();
extern void disable_irq_interrupt();
extern void enable_fiq_interrupt();
extern void disable_fiq_interrupt();
void kernel_syscall_dispatch(unsigned int args[]);
void kernel_main_loop();
void kernel_ready();
void kernel_scheduler_switch_context();
#endif