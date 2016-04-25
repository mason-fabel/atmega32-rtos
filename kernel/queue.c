#include <inttypes.h>
#include <stdlib.h>
#include "defines.h"

void _uik_queue_insert(_uik_queue_node_t *head, uint8_t pid) {
	_uik_queue_node_t *new;
	_uik_queue_node_t *ptr;

	new = malloc(sizeof(_uik_queue_node_t));
	new->pid = pid;
	new->next = NULL;

	if (head == NULL) {
		head = new;
	} else {
		for (ptr = head; ptr != NULL; ptr = ptr->next) {
			if (ptr->next == NULL) {
				ptr->next = new;
			} else if (
				_uik_task_table[new->pid]->pri 
				< _uik_task_table[(ptr->next)->pid]->pri
			) {
				new->next = ptr->next;
				ptr->next = new;
				break;
			}
		}
	}
}

uint8_t _uik_queue_next(_uik_queue_node_t *head) {
	uint8_t pid;
	_uik_queue_node_t *out;

	out = head;
	pid = head->pid;
	head = head->next;;

	free(out);

	return pid;
}
