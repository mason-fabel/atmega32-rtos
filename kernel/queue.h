#ifndef _KERNEL_QUEUE_H_
#define _KERNEL_QUEUE_H_

struct _uik_queue_node{
	uik_taskptr_t task;
	struct _uik_task_queue_node *next;
};
typedef struct _uik_queue_node _uik_queue_node_t;

_uik_queue_node_t _uik_queue_ready;
_uik_queue_node_t _uik_queue_blocked;

#endif /* _KERNEL_QUEUE_H_ */
