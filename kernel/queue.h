#ifndef _KERNEL_QUEUE_H_
#define _KERNEL_QUEUE_H_

#include <inttypes.h>
#include "defines.h"

struct _uik_queue_node{
	uint8_t pid;
	struct _uik_queue_node *next;
};
typedef struct _uik_queue_node _uik_queue_node_t;

void _uik_queue_insert(_uik_queue_node_t *head, uint8_t pid);
uint8_t _uik_queue_next(_uik_queue_node_t *head);
_uik_queue_node_t *_uik_queue_ready;

#endif /* _KERNEL_QUEUE_H_ */
