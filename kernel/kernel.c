#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>
#include <stdlib.h>
#include "kernel.h"

#define _UIK_PRIORITY_MAX 0
#define _UIK_PRIORITY_MIN 255
#define _UIK_TASK_IDLE_PID 0
#define _UIK_TASK_IDLE_STACK_LEN 64

void _uik_dispatch(void);

volatile uint8_t uik_task_active;
volatile uint8_t* _uik_active_sptr;
volatile uik_tcb_t _uik_tcb[TASKS_MAX];
uint8_t _uik_tasks_num = 0;
uint8_t _uik_active_task = 0;
uint32_t _uik_tick_num;

void _uik_task_idle(void);
uint8_t _uik_task_idle_stack[_UIK_TASK_IDLE_STACK_LEN] __attribute__((weak));

#define _uik_context_save() \
	asm volatile ( \
		"push r0 \n\t" \
		"in r0, __SREG__ \n\t" \
		"cli \n\t" \
		"push r0 \n\t" \
		"push r1 \n\t" \
		"clr r1 \n\t" \
		"push r2 \n\t" \
		"push r3 \n\t" \
		"push r4 \n\t" \
		"push r5 \n\t" \
		"push r6 \n\t" \
		"push r7 \n\t" \
		"push r8 \n\t" \
		"push r9 \n\t" \
		"push r10 \n\t" \
		"push r11 \n\t" \
		"push r12 \n\t" \
		"push r13 \n\t" \
		"push r14 \n\t" \
		"push r15 \n\t" \
		"push r16 \n\t" \
		"push r17 \n\t" \
		"push r18 \n\t" \
		"push r19 \n\t" \
		"push r20 \n\t" \
		"push r21 \n\t" \
		"push r22 \n\t" \
		"push r23 \n\t" \
		"push r24 \n\t" \
		"push r25 \n\t" \
		"push r26 \n\t" \
		"push r27 \n\t" \
		"push r28 \n\t" \
		"push r29 \n\t" \
		"push r30 \n\t" \
		"push r31 \n\t" \
		"lds r26, _uik_active_sptr \n\t" \
		"lds r27, _uik_active_sptr+1 \n\t" \
		"in r0, __SP_L__ \n\t" \
		"st x+, r0 \n\t" \
		"in r0, __SP_H__ \n\t" \
		"st x+, r0 \n\t" \
	);

#define _uik_context_restore() \
	asm volatile ( \
		"lds r26, _uik_active_sptr \n\t" \
		"lds r27, _uik_active_sptr+1 \n\t" \
		"ld r28, x+ \n\t" \
		"out __SP_L__, r28 \n\t" \
		"ld r29, x+ \n\t" \
		"out __SP_H__, r29 \n\t" \
		"pop r31 \n\t" \
		"pop r30 \n\t" \
		"pop r29 \n\t" \
		"pop r28 \n\t" \
		"pop r27 \n\t" \
		"pop r26 \n\t" \
		"pop r25 \n\t" \
		"pop r24 \n\t" \
		"pop r23 \n\t" \
		"pop r22 \n\t" \
		"pop r21 \n\t" \
		"pop r20 \n\t" \
		"pop r19 \n\t" \
		"pop r18 \n\t" \
		"pop r17 \n\t" \
		"pop r16 \n\t" \
		"pop r15 \n\t" \
		"pop r14 \n\t" \
		"pop r13 \n\t" \
		"pop r12 \n\t" \
		"pop r11 \n\t" \
		"pop r10 \n\t" \
		"pop r9 \n\t" \
		"pop r8 \n\t" \
		"pop r7 \n\t" \
		"pop r6 \n\t" \
		"pop r5 \n\t" \
		"pop r4 \n\t" \
		"pop r3 \n\t" \
		"pop r2 \n\t" \
		"pop r1 \n\t" \
		"pop r0 \n\t" \
		"out __SREG__, r0 \n\t" \
		"pop r0 \n\t" \
	);

void uik_initialize(uint8_t tick_len) {
	DDRB = 0xFF;

	TCCR0 = (1 << CS00) | (1 << CS01) | (1 << WGM01);
	TIMSK = (1<<OCIE0) ;
	TCNT0 = 0;
	OCR0 = tick_len;

	_uik_tick_num = 0;

	uik_task_add(&_uik_task_idle, _UIK_PRIORITY_MIN,
		_uik_task_idle_stack, _UIK_TASK_IDLE_STACK_LEN);

	return;
}

uint8_t uik_task_add(void tptr(void), uint8_t pri, uint8_t* sptr, uint16_t slen) {
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

void _uik_dispatch(void) {
	uint8_t i;
	uint8_t next_pid;
	
	next_pid = _UIK_TASK_IDLE_PID;

	for (i = 0; i < _uik_tasks_num; i++) {
		if (_uik_tcb[i].state != ready) {
			continue;
		}

		if (_uik_tcb[i].priority < _uik_tcb[next_pid].priority) {
			next_pid = i;
		}
	}

	_uik_active_task = next_pid;
	_uik_active_sptr = _uik_tcb[next_pid].sptr;

	return;
}

void uik_run(void)  {
	_uik_tcb[_UIK_TASK_IDLE_PID].state = ready;
	_uik_active_sptr = _uik_tcb[0].sptr;
	_uik_context_restore();
	asm volatile ("reti");
}

void _uik_task_idle() {
	while (1) PORTB = ~0x66;
}

ISR(TIMER0_COMP_vect,ISR_NAKED) {
	_uik_context_save();
	_uik_tick_num++;
	_uik_dispatch();
	_uik_context_restore();
	asm volatile ("reti");
}
