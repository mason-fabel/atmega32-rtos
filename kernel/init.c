#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>
#include <stdlib.h>
#include "defines.h"

void uik_initialize(uint16_t tick_len, uint8_t max_tasks) {
	uint8_t idle_pid;

	_uik_init_kernel(max_tasks);
	_uik_init_timer(tick_len);

	idle_pid = uik_task_add(_uik_task_idle, _UIK_TASK_PRIORITY_MIN,
		_UIK_TASK_STACK_MIN);
	uik_task_run(idle_pid);

	return;
}

void _uik_init_kernel(uint8_t max_tasks) {
	uint8_t i;

	_uik_task_next_pid = 0;
	_uik_task_active = 255;

	_uik_task_table = malloc(sizeof(_uik_tcb_t*) * max_tasks);
	for (i = 0; i < max_tasks; i++) {
		_uik_task_table[i] = NULL;
	}

	_uik_queue_ready = NULL;

	return;
}

void _uik_init_timer(uint16_t tick_len) {
	_uik_tick_len = tick_len;

	TCCR1A = _UIK_TIMER_MODE_CTC_A | _UIK_TIMER_MODE_NORMAL_PORT;
	TCCR1B = _UIK_TIMER_MODE_CTC_B | _UIK_TIMER_PRESCALER_1;

	TIMSK |= (0x01 << OCIE1A);

	TCNT1H = 0x00;
	TCNT1L = 0x00;

	OCR1A = _uik_tick_len;

	return;
}
