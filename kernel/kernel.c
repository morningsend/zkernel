#include "kernel.h"
#define MULTITASKING 0
#define KERNEL_TESTING 1

#ifdef KERNEL_TESTING
#include "test/kernel_tests.h"
#endif

static int timer_id;

void kernel_init(){
    PL011_puts(UART0, "kernel starting\n");
    init_pcb();
    init_scheduler();
#ifdef KERNEL_TESTING
    runKernelTests();
#endif
}

void kernel_device_init(){
    if(MULTITASKING == 1) {
        timer_id = request_timer_device();
        timer_set_ticks(timer_id, 0x4000);
        timer_set_periodic_mode(timer_id);
        timer_enable_interrupt(timer_id);
        timer_set_size_32bit(timer_id);
        timer_enable(timer_id);

        GICC0->PMR             = 0x000000F0; // unmask all            interrupts
        GICD0->ISENABLER[ 1 ] |= 0x00000010; // enable timer          interrupt
        GICC0->CTLR            = 0x00000001; // enable GIC interface
        GICD0->CTLR            = 0x00000001;

        enable_irq_interrupt();
    }

}
void kernel_scheduler_switch_context(){
    PL011_putc( UART0, 'T' );
    timer_clear_interrupt(timer_id);
}
void kernel_irq_handler() {
    // Step 2: read  the interrupt identifier so we know the source.
    uint32_t id = GICC0->IAR;
    disable_irq_interrupt();
    // Step 4: handle the interrupt, then clear (or reset) the source.
    switch(id){
        case GIC_SOURCE_TIMER0:
            kernel_scheduler_switch_context();
            break;
        case GIC_SOURCE_TIMER1:
            break;
        default:
            break;
    }

    GICC0->EOIR = id;
    enable_irq_interrupt();
}

void kernel_syscall_dispatch(unsigned int args[]){
    disable_irq_interrupt();
    uint32_t syscall_number = args[7];
    void* arg1 = (void *)args[0];
    void* arg2 = (void *)args[1];
    void* arg3 = (void *)args[2];

    int return_val = 0;
    switch(syscall_number){
        case SYSCALL_Exit:
            sys_exit((int) arg1);
            break;
        case SYSCALL_Write:
            return_val = sys_write((int) arg1,(char*) arg2,(unsigned int)arg3);
            break;
        case SYSCALL_Read:
            return_val = sys_read((int) arg1,(char*) arg2,(unsigned int)arg3);
            break;
        case SYSCALL_Yield:
            sys_yield();
            break;
        case SYSCALL_Execute:
            sys_execute((char*) arg1);
            break;
        case SYSCALL_Fork:
            return_val = sys_fork();
            break;
        default:
            syscall_def_handler(syscall_number);
            break;
    }
    args[0] = return_val;
    enable_irq_interrupt();
}

void kernel_ready(){
	user_init();
}

void kernel_shutdown(){
    PL011_puts(UART0,"kernel shutdown\n");
}