#ifndef _KERNEL_TASK_H_
#define _KERNEL_TASK_H_

#include <inttypes.h>
#include "defines.h"

#define _UIK_TASK_PRIORITY_MIN 0xFF
#define _UIK_TASK_PRIORITY_MAX 0x00
#define _UIK_TASK_STACK_MIN 50

struct _uik_stack {
	uint16_t len;
	void *head;
	void *ptr;
};
typedef struct _uik_stack _uik_stack_t;

struct _uik_tcb {
	uint8_t pid;
	uint8_t pri;
	uik_taskptr_t tptr;
	_uik_stack_t stk;
};
typedef struct _uik_tcb _uik_tcb_t;

uint8_t _uik_task_next_pid;

void _uik_task_idle(void);

#endif /* _KERNEL_TASK_H_ */
