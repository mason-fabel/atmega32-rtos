#ifndef _KERNEL_KERNEL_H_
#define _KERNEL_KERNEL_H_

#include <inttypes.h>

#define TASKS_MAX 8

enum _uik_task_state {
	wait,
	ready,
	initialized
};
typedef enum _uik_task_state uik_task_state_t;

typedef void (*uik_tptr_t)(void);

struct _uik_tcb {
	volatile uik_task_state_t state;
	uint8_t pid;
	uint8_t priority;
	uint8_t* sptr;
	uint16_t delay;
};
typedef struct _uik_tcb uik_tcb_t;

void uik_initialize(uint8_t tick_len);
void uik_run(void) __attribute__ ((naked));
void uik_delay(uint16_t ticks) __attribute__ ((naked));
void uik_task_run(uint8_t pid);
uint8_t uik_task_add(uik_tptr_t tptr, uint8_t pri, uint8_t* sptr, uint16_t slen);

#endif /* _KERNEL_KERNEL_H_ */
