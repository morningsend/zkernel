/*We define cpu mode constants*/
#include "arm.h"



.global reset_handler
.global kernel_idle
reset_handler:
	@LDR r0, =vector_table
	@MCR p15, 0, r0, c12, c0, 0 /* Set vector base address register to address of vector table*/

    bl vector_table_relocate

	/* go to svc, irq, etc., modes and set up stack */
irq_setup:
	mov r0, #MODE_IRQ
	orr r0, r0, #I_BIT
	orr r0, r0, #F_BIT
	msr cpsr_c, r0
	ldr sp, =irq_stack_base
    stmfd sp!, {r0-r12, lr}

svc_setup:
	mov r0, #MODE_SUPERVISOR
	orr r0, r0, #I_BIT
	orr r0, r0, #F_BIT
	msr cpsr, r0
	ldr sp, =svc_stack_base
    stmfd sp!, {r0-r12,lr}
    bl kernel_init

system_setup:
    mov r0, #MODE_SYS
    orr r0, r0, #I_BIT
    orr r0, r0, #F_BIT
    msr cpsr_c, r0
    ldr sp, =sys_stack_base
    stmfd sp!, {r0-r12, lr}

device_init:
    mov r0, #MODE_IRQ
    orr r0, r0, #I_BIT
    orr r0, r0, #F_BIT
    msr cpsr_c, r0
    bl kernel_device_init

kernel_init_finish:
    mov r0, #MODE_SUPERVISOR
    bl kernel_ready

kernel_idle:
    b kernel_idle

	b kernel_shutdown

undefined_handler:
	b undefined_handler

supervisor_call_handler:
    sub lr, lr, #0
    stmfd sp!, { r0-r12, sp, lr }^ @ store  USR registers
    mrs   r2, spsr                @ get    USR        CPSR
    stmfd sp!, { r2, lr }         @ store  USR PC and CPSR
    mov r0, sp
    bl    kernel_syscall_dispatch      @ invoke C function
    ldmfd sp!, { r2, lr }         @ load   USR mode PC and CPSR
    msr   spsr, r2                @ set    USR mode        CPSR
    ldmfd sp!, { r0-r12, sp, lr }^ @ load   USR mode registers

svc_before_return:
	movs  pc, lr                  @ return from interrupt

prefetch_abort_handler:
	b prefetch_abort_handler

data_abort_handler:
	b data_abort_handler

irq_handler:
	sub   lr, lr, #4              @ correct return address
	stmfd sp!, { r0-r3, ip, lr }  @ save    caller-save registers

	bl    kernel_irq_handler      @ invoke C function

	ldmfd sp!, { r0-r3, ip, lr }  @ restore caller-save registers
	movs  pc, lr                  @ return from interrupt

fiq_handler:
	b fiq_handler

vector_table:
	LDR pc, reset_address
	LDR pc, undefined_address
	LDR pc, supervisor_call_address
	LDR pc, prefetch_abort_address
	LDR pc, data_abort_address
	b .
	LDR pc, irq_address
	LDR pc, fiq_address

reset_address: .word reset_handler
undefined_address: .word undefined_handler
supervisor_call_address: .word supervisor_call_handler
prefetch_abort_address: .word prefetch_abort_handler
data_abort_address: .word data_abort_handler
irq_address: .word irq_handler
fiq_address: .word fiq_handler
kernel_ready_address: .word kernel_ready

vector_table_relocate:
    mov r0, #0
    ldr r1, =vector_table
    ldr r2, =vector_table_relocate

vec_reloc_loop:

    ldr r3, [r1], #4
    str r3, [r0], #4
    cmp r1,r2

    bne vec_reloc_loop

    mov pc, lr
@end vector_table_relocate




.global enable_irq_interrupt
.global disable_irq_interrupt
.global enable_fiq_interrupt
.global disable_fiq_interrupt
.global thread_context_init

enable_irq_interrupt:
	mrs r0, cpsr
	bic r0, r0, #I_BIT
	msr cpsr_c, r0
	mov pc, lr

disable_irq_interrupt:
	mrs r0, cpsr
	orr r0, r0, #I_BIT
	msr cpsr_c, r0
	mov pc, lr

enable_fiq_interrupt:
	mrs r0, cpsr
	bic r0, r0, #F_BIT
	msr cpsr_c, r0
	mov pc, lr

disable_fiq_interrupt:
	mrs r0, cpsr
	orr r0, r0, #F_BIT
	msr cpsr_c, r0
	mov pc, lr

thread_context_init:
    stmfd sp!, {r0-r3,lr}

    mov r0,#0x1F
    orr r0,r0, #0x80
    orr r0,r0, #0x40
    msr cpsr_c, r0

    mov sp, r5
    mov lr, r7
    stmfd sp!, { lr }^

    msr spsr, #MODE_USER
    movs pc, r6

    mov r0, #0
    mov r6, #1
    svc #0

    ldmfd sp!, {r0-r3,pc}

