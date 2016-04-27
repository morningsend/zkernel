#include "kernel.h"
#define MULTITASKING 1
#define KERNEL_TESTING 1

#ifdef KERNEL_TESTING
#include "test/kernel_tests.h"
#endif

static int timer_id;
static allocator kernel_allocator;
static allocator user_allocator;
static scheduler_t thread_scheduler;

p_thread create_thread(){
    p_thread th = mem_alloc(&kernel_allocator, sizeof(thread));
    void* stack = mem_alloc(&user_allocator, THREAD_STACK_SIZE);
    thread_create(th, PRIORITY_NORMAL, stack+THREAD_STACK_SIZE, THREAD_STACK_SIZE, user_init);
    thread_load_init_context(th);
    return th;
}
p_thread create_idle_thread(){
    p_thread th = mem_alloc(&kernel_allocator, sizeof(thread));
    void* stack = mem_alloc(&user_allocator, THREAD_STACK_SIZE);
    thread_create(th, PRIORITY_LOW, stack+THREAD_STACK_SIZE, THREAD_STACK_SIZE, user_idle);
    thread_load_init_context(th);
    return th;
}
void destroy_thread(p_thread th){
    void* memory = th->stack_base - th->stack_size;
    mem_free(&kernel_allocator, th);
    mem_free(&user_allocator, memory);
}


void init_mem_alloc(){
    init_alloc_with_pool(&kernel_allocator,& kernel_heap_base,(uint32_t) &kernel_heap_size);
    init_alloc_with_pool(&user_allocator, & user_heap_base, (uint32_t)&user_heap_size);
}

void kernel_init(){
    PL011_puts(UART0, "kernel starting\n");
    init_mem_alloc();
    init_scheduler(&thread_scheduler, &kernel_allocator);
    fs_init();
#ifdef KERNEL_TESTING
    runKernelTests();
#endif
}


void kernel_device_init(){
    if(MULTITASKING == 1) {
        timer_id = request_timer_device();
        timer_set_ticks(timer_id, 0x20000);
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
void kernel_switch_context(context* con){
    p_thread th = scheduler_get_current_thread(&thread_scheduler);
    thread_save_context(th, con);
    thread_suspend(th);
    scheduler_update(&thread_scheduler);
    th = scheduler_yield_next_thread(&thread_scheduler);
    memcpy(con, &th->ctx, sizeof(context));
    th->state = THREAD_STATE_RUNNING;
}
void kernel_schedule_next_thread(context* con){

    p_thread th = scheduler_get_current_thread(&thread_scheduler);
    thread_save_context(th, con);
    thread_suspend(th);
    scheduler_update(&thread_scheduler);
    th = scheduler_schedule_next(&thread_scheduler);
    memcpy(con, &th->ctx, sizeof(context));
    th->state = THREAD_STATE_RUNNING;

}
void kernel_fork_thread(){
    p_thread parent = scheduler_get_current_thread(&thread_scheduler);
    p_thread child = mem_alloc(&kernel_allocator, sizeof(thread));
    void* stack = mem_alloc(&kernel_allocator, sizeof(parent->stack_size));
    thread_fork(parent, child, stack);
    parent->ctx.registers[0] = child->id;
    child->ctx.registers[0] = 0;
    scheduler_schedule_thread(&thread_scheduler, child);
}
void kernel_irq_handler(context* con) {
    // Step 2: read  the interrupt identifier so we know the source.
    uint32_t id = GICC0->IAR;
    disable_irq_interrupt();
    // Step 4: handle the interrupt, then clear (or reset) the source.
    switch(id){
        case GIC_SOURCE_TIMER0:
            kernel_schedule_next_thread(con);
            timer_clear_interrupt(timer_id);
            break;
        case GIC_SOURCE_TIMER1:
            break;
        default:
            break;
    }
    GICC0->EOIR = id;
    enable_irq_interrupt();
}

void kernel_syscall_dispatch(context* exec_context){
    disable_irq_interrupt();
    uint32_t syscall_number = exec_context->registers[7];
    void* arg1 = (void *)exec_context->registers[0];
    void* arg2 = (void *)exec_context->registers[1];
    void* arg3 = (void *)exec_context->registers[2];
    p_thread th;
    int return_val = 0;
    switch(syscall_number){
        case SYSCALL_Exit:

            th = scheduler_kill_current_thread(&thread_scheduler);
            th->exit_code = (int) arg1;
            destroy_thread(th);
            scheduler_update(&thread_scheduler);
            th = scheduler_schedule_next(&thread_scheduler);
            memcpy(exec_context, &th->ctx, sizeof(context));
            th->state = THREAD_STATE_RUNNING;
            break;
        case SYSCALL_Write:
            return_val = sys_write((int) arg1,(char*) arg2,(unsigned int)arg3);
            exec_context->registers[0] = return_val;
            break;
        case SYSCALL_Read:
            return_val = sys_read((int) arg1,(char*) arg2,(unsigned int)arg3);
            exec_context->registers[0] = return_val;
            break;
        case SYSCALL_Yield:
            kernel_switch_context(exec_context);
            break;
        case SYSCALL_Execute:
            sys_execute(arg1);
            break;
        case SYSCALL_Fork:
            th = scheduler_get_current_thread(&thread_scheduler);
            thread_save_context(th, exec_context);
            kernel_fork_thread();
            break;
        case SYSCALL_Gettid:
            th = scheduler_get_current_thread(&thread_scheduler);
            exec_context->registers[0] = th->id;
            break;
        default:
            syscall_def_handler(syscall_number);
            break;
    }
    enable_irq_interrupt();
}

void kernel_ready(){
    p_thread th = create_thread();
    scheduler_schedule_thread(&thread_scheduler, th);
    th = create_idle_thread();
    scheduler_schedule_thread(&thread_scheduler, th);
    //..add some more threads to run
    scheduler_update(&thread_scheduler);
    th = scheduler_get_current_thread(&thread_scheduler);
    if(th != NULL) {
        thread_dispatch(th);
    }
    asm("b kernel_idle");
}

void kernel_shutdown(){
    PL011_puts(UART0,"kernel shutdown\n");
}
