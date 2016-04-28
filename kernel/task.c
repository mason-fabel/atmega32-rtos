#include <avr/io.h>
#include <inttypes.h>
#include "kernel.h"
#include "defines.h"

uint8_t uik_task_add(uik_tptr_t tptr, uint8_t pri, uint8_t* sptr, uint16_t slen) {
	uint16_t func_ptr;
	uint8_t* stack_ptr;
	uint8_t pid;

	if (_uik_tasks_num > TASKS_MAX) {
		return (-1);
	} else {
		pid = _uik_tasks_num;
		_uik_tasks_num++;
	}

	stack_ptr = sptr + slen - 1;

	_uik_tcb[pid].state = initialized;
	_uik_tcb[pid].priority = pri;
	_uik_tcb[pid].pid = pid;
	_uik_tcb[pid].sptr = stack_ptr - 1;

	*stack_ptr = 0x11; 
	stack_ptr--;
	*stack_ptr = 0x22; 
	stack_ptr--;
	*stack_ptr = 0x33;
	stack_ptr--;

	func_ptr = (uint16_t) tptr;
	*stack_ptr = func_ptr & 0x00FF;
	stack_ptr--;
	func_ptr >>= 8;
	*stack_ptr = func_ptr & 0x00FF;
	stack_ptr--;

	*stack_ptr = 0x00;
	stack_ptr--;
	*stack_ptr = 0x00;
	stack_ptr--;
	*stack_ptr = 0x00;
	stack_ptr--;
	*stack_ptr = 0x02;
	stack_ptr--;
	*stack_ptr = 0x03;
	stack_ptr--;
	*stack_ptr = 0x04;
	stack_ptr--;
	*stack_ptr = 0x05;
	stack_ptr--;
	*stack_ptr = 0x06;
	stack_ptr--;
	*stack_ptr = 0x07;
	stack_ptr--;
	*stack_ptr = 0x08;
	stack_ptr--;
	*stack_ptr = 0x09;
	stack_ptr--;
	*stack_ptr = 0x10;
	stack_ptr--;
	*stack_ptr = 0x11;
	stack_ptr--;
	*stack_ptr = 0x12;
	stack_ptr--;
	*stack_ptr = 0x13;
	stack_ptr--;
	*stack_ptr = 0x14;
	stack_ptr--;
	*stack_ptr = 0x15;
	stack_ptr--;
	*stack_ptr = 0x16;
	stack_ptr--;
	*stack_ptr = 0x17;
	stack_ptr--;
	*stack_ptr = 0x18;
	stack_ptr--;
	*stack_ptr = 0x19;
	stack_ptr--;
	*stack_ptr = 0x20;
	stack_ptr--;
	*stack_ptr = 0x21;
	stack_ptr--;
	*stack_ptr = 0x22;
	stack_ptr--;
	*stack_ptr = 0x23;
	stack_ptr--;
	*stack_ptr = 0x24;
	stack_ptr--;
	*stack_ptr = 0x25;
	stack_ptr--;
	*stack_ptr = 0x26;
	stack_ptr--;
	*stack_ptr = 0x27;
	stack_ptr--;
	*stack_ptr = 0x28;
	stack_ptr--;
	*stack_ptr = 0x29;
	stack_ptr--;
	*stack_ptr = 0x30;
	stack_ptr--;
	*stack_ptr = 0x31;
	stack_ptr--;
 
	func_ptr = (uint16_t) stack_ptr;
	*(_uik_tcb[pid].sptr) = (func_ptr & 0x00FF);
	func_ptr >>= 8;
	*(_uik_tcb[pid].sptr + 1) = (func_ptr & 0x00FF);
	
	return pid;
}

void uik_task_run(uint8_t pid) {
	_uik_tcb[pid].state = ready;

	return;
}

void _uik_task_idle() {
	while (1) PORTB = ~0x66;

	return;
}
