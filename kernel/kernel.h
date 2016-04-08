#ifndef _KERNEL_KERNEL_H_
#define _KERNEL_KERNEL_H_

#include <inttypes.h>

typedef void (*uik_taskptr_t)(void);

void    uik_initialize(uint16_t tick_len, uint8_t max_tasks);
uint8_t uik_task_add(uik_taskptr_t task, uint8_t priority, uint16_t stack_len);
void    uik_task_run(uint8_t id);
void    uik_schedule(void);

#endif /* _KERNEL_KERNEL_H_ */
