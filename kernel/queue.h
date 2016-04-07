#ifndef _KERNEL_QUEUE_H_
#define _KERNEL_QUEUE_H_

struct _uik_queue_node{
	_uik_tcb_t *task;
	struct _uik_queue_node *next;
};
typedef struct _uik_queue_node _uik_queue_node_t;

_uik_queue_node_t *_uik_queue_ready;

void _uik_queue_insert(_uik_queue_node_t *head, _uik_tcb_t *tcb);
_uik_tcb_t *_uik_queue_next(_uik_queue_node_t *head);

#endif /* _KERNEL_QUEUE_H_ */
