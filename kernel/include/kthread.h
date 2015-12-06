/*
 * kthread.h
 *
 *  Created on: Apr 23, 2015
 *      Author: mwkurian
 */

#ifndef KERNEL_INCLUDE_KTHREAD_H_
#define KERNEL_INCLUDE_KTHREAD_H_

#include "process.h"
#include "vm.h"

typedef void (*kthread_callback_handler)();

typedef struct kthread_handle {
    uint32_t parent_pid;
    int niceness;
    int state; 
    //use same state as parent
    //params
    //function pointer
    //put that in registers 
    //pc and arg0
    //perhaps pointer into pcb


    struct vas* stored_vas;
	/*
	struct vas* stored_vas;
	pcb* parent
	*/



	//ID data
	char* name; /* for debugging purposes */
	uint32_t starting_address;
	uint32_t process_number; // is this a mapping to actual executable image? or does it describe total number of processes?
	uint32_t (*function)();
	uint32_t has_executed;

	PROCESS_STATE current_state;

	/*
	 * r0-r3 are the argument and scratch registers; r0-r1 are also the result registers
	 * r4-r8 are callee-save registers
	 * r9 might be a callee-save register or not (on some variants of AAPCS it is a special register)
	 * r10-r11 are callee-save registers
	 * r12-r15 are special registers
	 * 37 REGISTERS IN TOTAL: 31 GPRs, 6 SRs
	 */

	// WE ARE GOING TO TRY TO IMPLEMENT SETJMP/LONGJMP INSTEAD OF MANUALLY DEALING WITH THESE VALUES
	// uint32_t PC;
	// uint32_t SP;
	// uint32_t CPSR; //current prog status register
	// uint32_t SPSR; //saved prog status register when execption occurs
	//unbanked register

	uint32_t R0;
	uint32_t R1;
	uint32_t R2;
	uint32_t R3;
	uint32_t R4;
	uint32_t R5;
	uint32_t R6;
	uint32_t R7;

	//banked registers
	uint32_t R8;
	uint32_t R9;
	uint32_t R10;
	uint32_t R11;
	uint32_t R12;
	uint32_t R13; //corresponds to the SP; do we need both?
	uint32_t R14;
	uint32_t R15; //corresponds to the PC; do we need both?

	uint32_t SPSR;
	uint32_t PC;

	void* heap_p;

    kthread_callback_handler cb_handler;

} kthread_handle;


kthread_handle* kthread_create(kthread_callback_handler cb_handler);
void init_thread_stack(kthread_handle* kthread);
uint32_t kthread_start(kthread_handle * kthread);
void execute_thread(kthread_handle* kthread);
void kthread_save_state(kthread_handle* kthread);
void kthread_load_state(kthread_handle* kthread);

#endif /* KERNEL_INCLUDE_KTHREAD_H_ */
