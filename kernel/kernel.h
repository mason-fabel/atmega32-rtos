#ifndef _UIK_H_
#define _UIK_H_

#include <inttypes.h>

#define TASKS_MAX 8

typedef enum {
	wait,
	ready,
	run,
	initialized,
	blocked
} uik_task_state_t;

typedef struct tcb {
	volatile uik_task_state_t state;
	uint8_t pid;
	uint8_t priority;
	uint8_t* sptr;
} uik_tcb_t;

void uik_initialize(uint8_t tick_len);
void uik_run(void) __attribute__ ((naked));
void uik_task_run(uint8_t pid);
uint8_t uik_task_add(void tptr(void), uint8_t pri, uint8_t* sptr, uint16_t slen);

#endif /* _UIK_H_ */
