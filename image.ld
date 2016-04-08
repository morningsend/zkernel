ENTRY(reset_handler)
SECTIONS {
  /* assign address (per  QEMU)  */
  .       =     0x70010000; 
  /* place text segment(s)       */
  .text : { kernel/boot.o(.text) *(.text .rodata) }
  /* place data segment(s)       */        
  .data : {                           *(.data        ) } 
  /* place bss  segment(s)       */        
  .bss  : {                           *(.bss         ) }
  
  /* align  address (per AAPCS)  */
  .       = ALIGN(8);        
  /* allocate stack for irq mode */
  .       = . + 0x00001000;  
  irq_stack_base = .;

  /* allocate stack for svc mode */
  .	= . + 0x00001000;
  svc_stack_base = .;

  . = . + 0x00001000;
  user_stack_base = .;
}