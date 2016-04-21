#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "../device/device.h"
#include "thread.h"
#include "../system/systemcall.h"
#include "sys_init.h"
#include "syscall_def.h"
#include "thread.h"
#include "context.h"
#include "schedule.h"
#include "../libc/allocator.h"

extern void* kernel_heap_base;
extern void* kernel_heap_size;
extern void* user_heap_size;
extern void* user_heap_base;
extern p_context current_thread_context;
void kernel_init();
void kernel_shutdown();
extern void enable_irq_interrupt();
extern void disable_irq_interrupt();
extern void enable_fiq_interrupt();
extern void disable_fiq_interrupt();
void kernel_syscall_dispatch(context* exec_context);
void kernel_ready();
void kernel_scheduler_switch_context();
p_context kernel_get_thread_context();
void kernel_set_thread_context(p_context p);

#endif