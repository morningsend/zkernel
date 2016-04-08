/*We define cpu mode constants*/
#include "boot.h"



 .global reset_handler

reset_handler:
	@LDR r0, =vector_table
	@MCR p15, 0, r0, c12, c0, 0 /* Set vector base address register to address of vector table*/

    bl vector_table_relocate

	/* go to svc, irq, etc., modes and set up stack */
	mov r0, #MODE_IRQ
	orr r0, r0, #I_BIT
	orr r0, r0, #F_BIT
	msr cpsr_c, r0
	ldr r1, =irq_stack_base
	mov sp, r1

	mov r0, #MODE_SUPERVISOR
	orr r0, r0, #I_BIT
	orr r0, r0, #F_BIT
	msr cpsr_c, r0
	ldr r1, =svc_stack_base
	mov sp, r1

	sub sp, sp, #68
	/* call kernel initialization function */
	mov r0, sp
	bl kernel_init
	ldmia sp!, { r0, lr }         @ load   USR mode PC and CPSR
	msr   spsr, r0                @ set    USR mode        CPSR
	ldmia sp, { r0-r12, sp, lr }^ @ load   USR mode registers
	add   sp, sp, #60             @ update SVC mode SP

    cmp lr, #0
    bne return_user_mode

    b kernel_ready
return_user_mode:
	movs  pc, lr                  @ return from interrupt
	b .

undefined_handler:
	b undefined_handler

supervisor_call_handler:
	sub   lr, lr, #0              @ correct return address
	sub   sp, sp, #60             @ update SVC mode stack
	stmia sp, { r0-r12, sp, lr }^ @ store  USR registers
	mrs   r0, spsr                @ get    USR        CPSR
	stmdb sp!, { r0, lr }         @ store  USR PC and CPSR

	mov   r1, sp                  @ set    C function arg. = SP
	ldr   r0, [ lr, #-4 ]         @ load                     svc instruction
	bic   r0, r0, #0xFF000000     @ set    C function arg. = svc immediate
	bl    kernel_svc_handler      @ invoke C function

	ldmia sp!, { r0, lr }         @ load   USR mode PC and CPSR
	msr   spsr, r0                @ set    USR mode        CPSR
	ldmia sp, { r0-r12, sp, lr }^ @ load   USR mode registers
	add   sp, sp, #60             @ update SVC mode SP
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
	B .
	LDR pc, irq_address
	LDR pc, fiq_address

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

reset_address: .word reset_handler
undefined_address: .word undefined_handler
supervisor_call_address: .word supervisor_call_handler
prefetch_abort_address: .word prefetch_abort_handler
data_abort_address: .word data_abort_handler
irq_address: .word irq_handler
fiq_address: .word fiq_handler


.global enable_irq_interrupt
.global disable_irq_interrupt
.global enable_fiq_interrupt
.global disable_fiq_interrupt

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


/* Interrupt handlers */
/* unimplemented handlers will branch to itself causing a halt */


/* The reset handler is the first code that runs when CPU boots up
 * We need to initialize the stack pointers, invalidate cache and
 * setup MMU and branch to C code which containers kernel initialization code.
 */
