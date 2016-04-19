ENTRY(reset_handler)
SECTIONS {
  /* assign address (per  QEMU)  */
  .       =     0x70010000;
  start = .;
  /* place text segment(s)       */
  .text : {
    CMakeFiles/kernel.dir/kernel/boot.S.o(.text)
    *(.text .rodata)
    }
  /* place data segment(s)       */        
  .data : {                           *(.data        ) } 
  /* place bss  segment(s)       */        
  .bss  : {                           *(.bss         ) }
  
  /* align  address (per AAPCS)  */
  .       = ALIGN(8);        
  /* allocate stack for irq mode */
  .       = . + 0x00004000;
  irq_stack_base = .;

  /* allocate stack for svc mode */
  .	= . + 0x00004000;
  svc_stack_base = .;
  kernel_heap_size = 4M;
  . += 0x1000;
  kernel_heap_base = .;
  . += kernel_heap_size;

  . = . + 0x00004000;
  user_stack_base = .;

  /* PROVIDE (end = .); */
}