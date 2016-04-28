#ifndef _KERNEL_TASK_H_
#define _KERNEL_TASK_H_

#define _UIK_PRIORITY_MAX 0
#define _UIK_PRIORITY_MIN 255
#define _UIK_TASK_IDLE_PID 0
#define _UIK_TASK_IDLE_STACK_LEN 64

volatile uint8_t _uik_active_task;
volatile uint8_t* _uik_active_sptr;
volatile uik_tcb_t _uik_tcb[TASKS_MAX];
uint8_t _uik_tasks_num;

void _uik_task_idle(void);
uint8_t _uik_task_idle_stack[_UIK_TASK_IDLE_STACK_LEN] __attribute__((weak));

#endif /* _KERNEL_TASK_H_ */
