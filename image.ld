user_heap_size = 0x400000;
kernel_heap_size = 0x100000;

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
  stack_size = 0x8000;
  /* align  address (per AAPCS)  */
  .       = ALIGN(8);        
  /* allocate stack for irq mode */
  .       = . + stack_size;
  irq_stack_base = .;

  /* allocate stack for svc mode */
  .	= . + stack_size;
  svc_stack_base = .;
  . += stack_size;
  sys_stack_base = .;
  . += 0x1000;
  kernel_heap_base = .;
  . += kernel_heap_size;
  . += 0x1000;
  user_heap_base = .;
  . += user_heap_size;
  . += 0x1000;
  . = . + stack_size;
  user_stack_base = .;
  . += 0x1000;

  /* PROVIDE (end = .); */
}