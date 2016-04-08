#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdlib.h>
#include "defines.h"

uint8_t uik_task_add(uik_taskptr_t task, uint8_t priority, uint16_t stack_len) {
	_uik_tcb_t *new;

	cli();

	new = (_uik_tcb_t*) malloc(sizeof(_uik_tcb_t));
	new->pid = _uik_task_next_pid;
	new->pri = priority;
	new->tptr = task;
	(new->stk).len = stack_len;
	(new->stk).head = malloc(sizeof(stack_len));
	(new->stk).ptr = (new->stk).head;

	_uik_task_table[_uik_task_next_pid] = new;

	_uik_task_next_pid++;

	sei();

	return new->pid;
}

void uik_task_run(uint8_t pid) {
	cli();

	_uik_queue_insert(_uik_queue_ready, pid);

	sei();

	return;
}

void uik_schedule(void) {
	cli();

	/* TODO:
	 * Implement me!
	 */

	sei();

	return;
}

void _uik_task_idle(void) {
	while(1) {
		/* do nothing */
	}

	return;
}
