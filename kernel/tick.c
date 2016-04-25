#include <avr/interrupt.h>
#include <stdlib.h>
#include "defines.h"

uint8_t sptr_tmp;

ISR(TIMER1_COMPA_vect, ISR_NAKED) {
	asm volatile (
		"push r0 \n\t"
		"push r1 \n\t"
		"push r2 \n\t"
		"push r3 \n\t"
		"push r4 \n\t"
		"push r5 \n\t"
		"push r6 \n\t"
		"push r7 \n\t"
		"push r8 \n\t"
		"push r9 \n\t"
		"push r10 \n\t"
		"push r11 \n\t"
		"push r12 \n\t"
		"push r13 \n\t"
		"push r14 \n\t"
		"push r15 \n\t"
		"push r16 \n\t"
		"push r17 \n\t"
		"push r18 \n\t"
		"push r19 \n\t"
		"push r20 \n\t"
		"push r21 \n\t"
		"push r22 \n\t"
		"push r23 \n\t"
		"push r24 \n\t"
		"push r25 \n\t"
		"push r26 \n\t"
		"push r27 \n\t"
		"push r28 \n\t"
		"push r29 \n\t"
		"push r30 \n\t"
		"push r31 \n\t"
		"lds r0, __SREG__ \n\t"
		"push r0 \n\t"
	);

	_uik_tick_num++;

	if (_uik_task_active == 255) {
		/* Do nothing */
	} else {
		/* Save stack pointer */
		asm volatile (
			"ldi r20, __SP_L__ \n\t"
			"sts sptr_tmp, r20 \n\t"
		);
		(_uik_task_table[_uik_task_active]->stk).sptr_l = sptr_tmp;
		asm volatile (
			"ldi r20, __SP_H__ \n\t"
			"sts sptr_tmp, r20 \n\t"
		);
		(_uik_task_table[_uik_task_active]->stk).sptr_h = sptr_tmp;

		while (1) PORTB = ~0x55;
	}

	_uik_task_active = _uik_queue_ready->pid;

// 	sptr_tmp = (_uik_task_table[_uik_task_active]->stk).sptr_l;
// 	asm volatile (
// 		"ldi r20, sptr_tmp \n\t"
// 		"out __SP_L__, r20 \n\t"
// 	);
// 	sptr_tmp = (_uik_task_table[_uik_task_active]->stk).sptr_h;
// 	asm volatile (
// 		"ldi r20, sptr_tmp \n\t"
// 		"out __SP_H__, r20 \n\t"
// 	);

	asm volatile (
		"pop r0 \n\t"
		"sts __SREG__, r0 \n\t"
		"pop r31 \n\t"
		"pop r30 \n\t"
		"pop r29 \n\t"
		"pop r28 \n\t"
		"pop r27 \n\t"
		"pop r26 \n\t"
		"pop r25 \n\t"
		"pop r24 \n\t"
		"pop r23 \n\t"
		"pop r22 \n\t"
		"pop r21 \n\t"
		"pop r20 \n\t"
		"pop r19 \n\t"
		"pop r18 \n\t"
		"pop r17 \n\t"
		"pop r16 \n\t"
		"pop r15 \n\t"
		"pop r14 \n\t"
		"pop r13 \n\t"
		"pop r12 \n\t"
		"pop r11 \n\t"
		"pop r10 \n\t"
		"pop r9 \n\t"
		"pop r8 \n\t"
		"pop r7 \n\t"
		"pop r6 \n\t"
		"pop r5 \n\t"
		"pop r4 \n\t"
		"pop r3 \n\t"
		"pop r2 \n\t"
		"pop r1 \n\t"
		"pop r0 \n\t"
	);

	asm volatile (
		// "reti \n\t"
		"ret \n\t"
	);
}
