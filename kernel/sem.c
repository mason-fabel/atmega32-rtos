#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "kernel.h"
#include "defines.h"

void uik_sem_create(uint8_t id, uint8_t val) {
	_uik_sem[id] = val;

	return;
}

void uik_sem_signal(uint8_t id) {
	uint8_t enqueued;
	uint8_t i;
	uint8_t pid;
	uint8_t pri;

	asm volatile ("cli");

	enqueued = _uik_sem[id] < 0;

	_uik_sem[id]++;

	if (enqueued) {
		pid = _UIK_TASK_IDLE_PID;
		pri = _UIK_PRIORITY_MIN;
		for (i = 0; i < _uik_tasks_num; i++) {
			switch (_uik_tcb[i].state) {
				case wait_sem:
					if (_uik_tcb[i].sid == id && _uik_tcb[i].priority < pri) {
						pid = i;
						pri = _uik_tcb[i].priority;
					}

					break;

				default:
					break;
			}
		}

		_uik_tcb[pid].state = ready;
	}

	asm volatile ("sei");

	return;
}

void uik_sem_wait(uint8_t id) {
	asm volatile ("cli");

	_uik_sem[id]--;

	if (_uik_sem[id] < 0) {
		_uik_context_save();
		_uik_tcb[_uik_active_task].state = wait_sem;
		_uik_tcb[_uik_active_task].sid = id;
		_uik_dispatch();
		_uik_context_restore();
		asm volatile ("reti");
	}

	asm volatile ("sei");

	return;
}
