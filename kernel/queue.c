#include <stdlib.h>
#include "defines.h"

void _uik_queue_insert(_uik_queue_node_t *head, _uik_tcb_t *tcb) {
	_uik_queue_node_t *new;
	_uik_queue_node_t *ptr;

	new = malloc(sizeof(_uik_queue_node_t));
	new->task = tcb;
	new->next = NULL;

	for (ptr = head; ptr != NULL; ptr = ptr->next) {
		if (new->task->pri > ptr->task->pri) {
			new->next = ptr->next;
			ptr->next = new;
			break;
		} else if (ptr->next == NULL) {
			ptr->next = new;
		}
	}
}

_uik_tcb_t *_uik_queue_next(_uik_queue_node_t *head) {
	_uik_queue_node_t *next;
	_uik_tcb_t *out;

	out = head->task;
	next = head->next;

	free(head);

	head = next;

	return out;
}
