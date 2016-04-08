#include "kernel.h"



void kernel_init(int* a){
	TIMER0->Timer1Load     = 0x00080000; 
	TIMER0->Timer1Ctrl     = 0x00000042; 
	TIMER0->Timer1Ctrl    |= 0x000000A0; 

	GICC0->PMR             = 0x000000F0; 
	GICD0->ISENABLER[ 1 ] |= 0x00000001; 
	GICC0->CTLR            = 0x00000001; 
	GICD0->CTLR            = 0x00000001;
    
	enable_irq_interrupt();
	enable_fiq_interrupt();
	PL011_putc(UART0, 'A');

	asm("svc #1");
}


void kernel_irq_handler() {
  // Step 2: read  the interrupt identifier so we know the source.

  uint32_t id = GICC0->IAR;

  // Step 4: handle the interrupt, then clear (or reset) the source.

  if( id == GIC_SOURCE_TIMER0 ) {
    PL011_putc( UART0, 'T' ); TIMER0->Timer1IntClr = 0x01;
  }

  // Step 5: write the interrupt identifier to signal we're done.

  GICC0->EOIR = id;
}

void kernel_svc_handler(int id, void* sp){
	PL011_putc(UART0,(char)id+'0');
	switch(id){
		case 0:
			PL011_putc(UART0,'s');
			break;
		default:
			break;
	}
}

void kernel_ready(){
	system_init();
}