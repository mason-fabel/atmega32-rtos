#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdlib.h>
#include "defines.h"

#include <util/delay.h>

uint8_t _sptr_l_tmp;
uint8_t _sptr_h_tmp;

uint8_t uik_task_add(uik_taskptr_t task, uint8_t priority, uint16_t stack_len) {
	uint8_t* sptr;
	uint8_t i;
	_uik_tcb_t *new;

	new = (_uik_tcb_t*) malloc(sizeof(_uik_tcb_t));
	new->pid = _uik_task_next_pid;
	new->pri = priority;
	new->tptr = task;

	(new->stk).len = stack_len;
	(new->stk).ptr = malloc(sizeof(stack_len));

	sptr = (uint8_t*) ((uint16_t) (new->stk).ptr
		+ (uint16_t) (new->stk.len) - 1);

	*sptr = 0x11;
	sptr--;
	*sptr = 0x22;
	sptr--;
	*sptr = 0x33;
	sptr--;

	*sptr = (uint8_t) ((uint16_t) task) & 0x00FF;
	sptr--;
	*sptr = (uint8_t) (((uint16_t) task) & 0xFF00) >> 8;
	sptr--;
	for (i = 0; i < 32; i++) {
		*sptr = 0x00;
		sptr--;
	}
	*sptr = 0x00;
	sptr--;

	(new->stk).sptr_l = ((uint16_t) sptr) & 0x00FF;
	(new->stk).sptr_h = (((uint16_t) sptr) & 0xFF00) >> 8;

	_uik_task_table[_uik_task_next_pid] = new;

	_uik_task_next_pid++;

	return new->pid;
}

void uik_task_run(uint8_t pid) {
	_uik_queue_insert(_uik_queue_ready, pid);

	return;
}

void _uik_task_idle(void) {

	while(1) {
		PORTB = ~0x66;
	}

	return;
}
