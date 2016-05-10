#ifndef _KERNEL_KERNEL_H_
#define _KERNEL_KERNEL_H_

#include <inttypes.h>

#define TASKS_MAX 10
#define SEM_MAX 10

enum _uik_task_state {
	initialized,
	ready,
	wait_delay,
	wait_event,
	wait_sem
};
typedef enum _uik_task_state uik_task_state_t;

typedef void (*uik_tptr_t)(void);

struct _uik_tcb {
	volatile uik_task_state_t state;
	uint8_t pid;
	uint8_t priority;
	uint8_t* sptr;
	uint32_t delay;
	uint8_t sid;
	uint8_t event;
};
typedef struct _uik_tcb uik_tcb_t;

void uik_initialize(uint8_t tick_len);
void uik_run(void) __attribute__ ((naked));

void uik_task_run(uint8_t pid);
uint8_t uik_task_add(uik_tptr_t tptr, uint8_t pri, uint8_t* sptr, uint16_t slen);

void uik_delay(uint32_t cycles) __attribute__ ((naked));

void uik_sem_create(uint8_t id, uint8_t val);
void uik_sem_signal(uint8_t id);
void uik_sem_wait(uint8_t id);

void uik_event_assoc(uint8_t eid);
void uik_event_disassoc(uint8_t pid, uint8_t eid);
void uik_event_raise(uint8_t eid);

#endif /* _KERNEL_KERNEL_H_ */
