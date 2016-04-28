#include <avr/interrupt.h>
#include "kernel.h"
#include "defines.h"

ISR(TIMER0_COMP_vect, ISR_NAKED) {
	_uik_context_save();
	_uik_tick_num++;
	_uik_dispatch();
	_uik_context_restore();
	asm volatile ("reti");

	return;
}

void _uik_dispatch(void) {
	uint8_t i;
	uint8_t next_pid;
	
	next_pid = _UIK_TASK_IDLE_PID;

	for (i = 0; i < _uik_tasks_num; i++) {
		if (_uik_tcb[i].state != ready) {
			continue;
		}

		if (_uik_tcb[i].priority < _uik_tcb[next_pid].priority) {
			next_pid = i;
		}
	}

	_uik_active_task = next_pid;
	_uik_active_sptr = _uik_tcb[next_pid].sptr;

	return;
}
