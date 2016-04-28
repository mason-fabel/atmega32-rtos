#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>
#include <stdlib.h>
#include "kernel.h"
#include "defines.h"

void uik_initialize(uint8_t tick_len) {
	DDRB = 0xFF;

	TCCR0 = (1 << CS00) | (1 << CS01) | (1 << WGM01);
	TIMSK = (1<<OCIE0) ;
	TCNT0 = 0;
	OCR0 = tick_len;

	_uik_tick_num = 0;
	_uik_tick_len = tick_len;

	_uik_tasks_num = 0;

	uik_task_add(&_uik_task_idle, _UIK_PRIORITY_MIN,
		_uik_task_idle_stack, _UIK_TASK_IDLE_STACK_LEN);

	return;
}

void uik_run(void)  {
	_uik_tcb[_UIK_TASK_IDLE_PID].state = ready;
	_uik_active_task = _UIK_TASK_IDLE_PID;
	_uik_active_sptr = _uik_tcb[0].sptr;
	_uik_context_restore();
	asm volatile ("reti");

	return;
}

void uik_delay(uint16_t ticks) {
	_uik_context_save();
	_uik_tcb[_uik_active_task].state = wait;
	_uik_tcb[_uik_active_task].delay = ticks / _uik_tick_len;
	_uik_dispatch();
	_uik_context_restore();
	asm volatile ("reti");

	return;
}
