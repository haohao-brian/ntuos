#include "kernel/types.h"
// #include "kernel/param.h"
// #include "kernel/memlayout.h"
// #include "kernel/riscv.h"
// #include "kernel/spinlock.h"
// #include "kernel/proc.h"
// #include "kernel/defs.h"

#include "user/setjmp.h"
#include "user/threads.h"
#include "user/user.h"

#define NULL 0
#define STACK_SIZE 0x100*8
extern void thread_switch(uint64 old, uint64 new);
static struct thread* current_thread = NULL;
static int id = 1;
static jmp_buf env_st;
// static jmp_buf env_tmp;
void dispatch(void){
    // YOUR CODE HERE
    if(setjmp(current_thread->previous->env)==0){
        if (current_thread->buf_set==1){
            longjmp(current_thread->env,1);
        }else {
            current_thread->buf_set = 1;
            thread_switch((uint64) &current_thread->previous->ctx, (uint64) &current_thread->ctx);
            current_thread->fp(NULL);
        }
    }
}
void schedule(void){
    current_thread = current_thread->next;
}


struct thread *thread_create(void (*func)(void *), void *arg){
// YOUR CODE HERE
    struct thread *tt = (struct thread*) malloc(sizeof(struct thread));
    tt->fp = func;
    tt->ID  = id;
    tt->buf_set = 0;

    unsigned long new_stack_p;
    unsigned long new_stack;
    new_stack = (unsigned long) malloc(sizeof(unsigned long)*0x100);
    new_stack_p = new_stack +0x100*8-0x2*8;
    tt->stack = (void*) new_stack;
    tt->stack_p = (void*) new_stack_p;

    tt->ctx.ra = (uint64) func;
    tt->ctx.sp = (uint64) tt->stack_p;
    id++;
    return tt;
}
void print(char *cc){
    printf("%s",cc);
    struct thread *i = current_thread;
    while(i->next!=current_thread){
        printf("%d ",i->ID);
        i = i->next;
    }
    printf("%d\n",i->ID);
}
void thread_add_runqueue(struct thread *tt){
    //addqueque
    if(current_thread == NULL){
        current_thread = tt;
        current_thread->next = current_thread;
        current_thread->previous = current_thread;
        // TODO
    }
    else{
        tt->next = current_thread;
        tt->previous = current_thread->previous;
        current_thread->previous->next = tt;
        current_thread->previous = tt;
    }
}
void thread_yield(void){
    schedule();
    dispatch();
}
void thread_exit(void){
    // printf("thread_exit %d\n",current_thread->ID);
    struct thread *tmp = current_thread->next;
    if(current_thread->next != current_thread){
        current_thread->previous->next = current_thread->next;
        current_thread->next->previous = current_thread->previous;
        free(current_thread->stack);
        free(current_thread);
        current_thread = tmp;
        //thread_schedule();
        // dispatch();
        // TODO
        longjmp(current_thread->env,1);
    }
    else{
        free(current_thread->stack);
        free(current_thread);
        current_thread = tmp;
        longjmp(env_st,1);
        // TODO
        // Hint: No more thread to execute
    }
}

void thread_start_threading(void){
    // TODO
    if (setjmp(env_st)==0){
        dispatch();
    }
}

// part 2
void thread_assign_task(struct thread *t, void (*f)(void *), void *arg){
    // TODO
}
