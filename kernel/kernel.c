#include "kernel.h"



void kernel_init(){
    PL011_puts(UART0, "kernel starting\n");
	TIMER0->Timer1Load     = 0x00080000; 
	TIMER0->Timer1Ctrl     = 0x00000042; 
	TIMER0->Timer1Ctrl    |= 0x000000A0; 

	GICC0->PMR             = 0x000000F0; 
	GICD0->ISENABLER[ 1 ] |= 0x00000001;
	GICC0->CTLR            = 0x00000001;
	GICD0->CTLR            = 0x00000001;

    system_init();
    enable_irq_interrupt();
    enable_fiq_interrupt();
}


void kernel_irq_handler() {
    // Step 2: read  the interrupt identifier so we know the source.

    uint32_t id = GICC0->IAR;

    // Step 4: handle the interrupt, then clear (or reset) the source.

    if( id == GIC_SOURCE_TIMER0 ) {
        PL011_putc( UART0, 'T' );
        TIMER0->Timer1IntClr = 0x01;
    }

    // Step 5: write the interrupt identifier to signal we're done.

    GICC0->EOIR = id;
}

void kernel_syscall_dispatch(unsigned int args[]){
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
        default:
            syscall_def_handler(syscall_number);
            break;
    }
    args[0] = return_val;
}

void kernel_ready(){
	user_init();
}

void kernel_shutdown(){
    PL011_puts(UART0,"kernel shutdown\n");
}