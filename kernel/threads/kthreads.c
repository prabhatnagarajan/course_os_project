/*
 * kthreads.c
 *
 *  Created on: Apr 23, 2015
 *      Author: mwkurian
 */

#include "kthread.h"
#include "scheduler.h"
#include "klibc.h"
#include <global_defs.h>


void execute_thread(kthread_handle* kthread)
{
/*
	//assert(pcb_p);

	//Copy the current process's program counter to the new process's return register
	//The new process will use R14 to return to the parent function
	asm("MOV %0, r15":"=r"(kthread->R14)::);

	//Switch to user virtual address space, this is self explanatory

	//Should be disabled once scheduler is working to prevent spam
	os_printf("Should be VAS: %x\n", vm_get_current_vas());

	//5-1-15: The following commented stuff is obsolete and only included for work reference
	//assert(1==2 && "process.c - We're stopping right after loading process state.");
	//4-15-15: Since execute_process is for new processes only, stored_vas must be empty 
	// assert(!pcb_p->stored_vas && "Assert error: trying to enter execute_process with already initialized process!");
	//4-13-15: Create new virtual address space for process and switch into it
	// Let's get a simple argc/argv layout going at 0x9f000000
	// Stick the program name at stack_base

	vm_enable_vas(kthread->stored_vas);
	

	//print_process_state(pcb_p->PID);

	kthread->has_executed = 1;

	//Set state to running, this should be modified when the process is tossed into wait queues, etc
	//Check header file for a list of states
	kthread->current_state = PROCESS_RUNNING;

	os_printf("thread state\n"); 

	//This will overwrite all our operating registers with the ones saved in the struct.
	//As soon as this is called the processor will start executing the new process.
	kthread_load_state(kthread);
*/
}

//changed to take in args
kthread_handle* kthread_create(kthread_callback_handler cb_handler)
{
	
	os_printf("entered thread_create \n");
	vm_use_kernel_vas();
	kthread_handle * kthread = kmalloc(sizeof(kthread_handle));
/*	
	os_printf("entered thread_create 2\n");
	kthread->parent_pid = get_process_pid();
	kthread->cb_handler = cb_handler;
	kthread->niceness = 0;

	kthread->R0 = 0;
	kthread->R1 = 0;
	kthread->R2 = 0;
	kthread->R3 = 0;
	kthread->R4 = 0;
	kthread->R5 = 0;
	kthread->R6 = 0;
	kthread->R7 = 0;

	kthread->R8 = 0;
	kthread->R9 = 0;
	kthread->R10 = 0;
	kthread->R11 = 0;
	kthread->R12 = 0;

	kthread->stored_vas = get_PCB(kthread->parent_pid)->stored_vas;


	os_printf("entered thread_create 3\n");

	init_thread_stack(kthread);
unncomment eventuall
*/
/*
	vm_use_kernel_vas();

	//malloc stack
	//uint32_t BASE = (uint32_t) umalloc(BLOCK_SIZE); //points to base of stack
	os_printf("BASE is %d\n",BASE);
	uint32_t sp = BASE + BLOCK_SIZE;
	//kthread->R13 = sp; //SP

	os_printf("entered thread_create 4\n");

	// Stick a NULL at STACK_TOP-sizeof(int*)
	uint32_t *stack_top = (uint32_t*) sp;
	stack_top[-1] = 0;
	stack_top[-2] = 0;
	stack_top[-3] = 0;
	stack_top[-4] = 0;
	stack_top[-5] = BASE;
	stack_top[-6] = 1;

	// We need to set sp (r13) to stack_top - 12
	kthread->R13 = sp - 4 * 6;

	//kthread->R13 = 0;
*/

//	kthread->R14 = 0;
//	kthread->R15 = 0; //PC

	return kthread;

}

void init_thread_stack(kthread_handle* kthread)
{

	vm_use_kernel_vas();

	uint32_t BASE = (uint32_t) kmalloc(BLOCK_SIZE);
	
	uint32_t sp = BASE + BLOCK_SIZE;

	// Stick a NULL at STACK_TOP-sizeof(int*)
	uint32_t *stack_top = (uint32_t*) sp;
	stack_top[-1] = 0;
	stack_top[-2] = 0;
	stack_top[-3] = 0;
	stack_top[-4] = 0;
	stack_top[-5] = STACK_BASE;
	stack_top[-6] = 1;

	// We need to set sp (r13) to stack_top - 12
	kthread->R13 = sp - 4 * 6;
}

uint32_t kthread_start(kthread_handle * kthread)
{
	os_printf("About to start Thread \n");
	sched_task * task = sched_create_task_from_kthread(kthread,10); 
	//remove below line	
	//sched_task * task = sched_create_task(kthread);
	sched_add_task(task);
	return  0;
}

void kthread_save_state(kthread_handle* kthread)
{
	asm("MOV %0, r0":"=r"(kthread->R0)::);
	asm("MOV %0, r1":"=r"(kthread->R1)::);
	asm("MOV %0, r2":"=r"(kthread->R2)::);
	asm("MOV %0, r3":"=r"(kthread->R3)::);
	asm("MOV %0, r4":"=r"(kthread->R4)::);
	asm("MOV %0, r5":"=r"(kthread->R5)::);
	asm("MOV %0, r6":"=r"(kthread->R6)::);
	asm("MOV %0, r7":"=r"(kthread->R7)::);
	asm("MOV %0, r8":"=r"(kthread->R8)::);
	asm("MOV %0, r9":"=r"(kthread->R9)::);
	asm("MOV %0, r10":"=r"(kthread->R10)::);
	asm("MOV %0, r11":"=r"(kthread->R11)::);
	asm("MOV %0, r12":"=r"(kthread->R12)::);
	asm("MOV %0, r13":"=r"(kthread->R13)::);
	asm("MOV %0, r14":"=r"(kthread->R14)::);
	asm("MOV %0, r15":"=r"(kthread->R15)::);
}

void kthread_load_state(kthread_handle* kthread)
{
	asm("MOV r0, %0"::"r"(kthread->R0):);
	asm("MOV r1, %0"::"r"(kthread->R1):);
	asm("MOV r2, %0"::"r"(kthread->R2):);
	asm("MOV r3, %0"::"r"(kthread->R3):);
	asm("MOV r4, %0"::"r"(kthread->R4):);
	asm("MOV r5, %0"::"r"(kthread->R5):);
	asm("MOV r6, %0"::"r"(kthread->R6):);
	asm("MOV r7, %0"::"r"(kthread->R7):);
	asm("MOV r8, %0"::"r"(kthread->R8):);
	asm("MOV r9, %0"::"r"(kthread->R9):);
	asm("MOV r10, %0"::"r"(kthread->R10):);
	//asm("MOV r11, %0"::"r"(11):);
	asm("MOV r12, %0"::"r"(kthread->R12):);

	asm("MOV r13, %0"::"r"(kthread->R13):);

	asm("MOV r14, %0"::"r"(kthread->R14):);
	//assert(1==11);
	
	os_printf("About to load PC into thread \n");

	os_printf("PC Value is %u \n", kthread->R15);

	asm("MOV r15, %0"::"r"(kthread->R15):); 

	__builtin_unreachable();
}

