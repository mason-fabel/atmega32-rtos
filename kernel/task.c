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

	_uik_task_next_pid++;

	_uik_queue_insert(_uik_queue_blocked, new);

	sei();

	return new->pid;
}

void uik_task_run(uint8_t pid) {
	_uik_queue_node_t *ptr;
	_uik_queue_node_t *node;
	_uik_tcb_t *task;

	cli();

	task = NULL;

	for (ptr = _uik_queue_blocked; ptr->next != NULL; ptr = ptr->next) {
		if (((ptr->next)->task)->pid == pid) {
			node = ptr->next;
			task = node->task;

			ptr->next = node->next;

			free(node);

			_uik_queue_insert(_uik_queue_ready, task);

			break;
		}
	}

	if (task == NULL) {
		/* unable to find task */
	}

	sei();

	return;
}

void uik_schedule(void) {
	/* TODO:
	 * Implement me!
	 */

	return;
}

void _uik_task_idle(void) {
	while(1) {
		/* do nothing */
	}

	return;
}
