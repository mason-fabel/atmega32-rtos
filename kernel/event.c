#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "kernel.h"
#include "defines.h"

void uik_event_assoc(uint8_t eid) {
	asm volatile ("cli");

	_uik_context_save();
	_uik_tcb[_uik_active_task].state = wait_event;
	_uik_tcb[_uik_active_task].event = eid;
	_uik_dispatch();
	_uik_context_restore();
	asm volatile ("reti");

	return;
}

void uik_event_disassoc(uint8_t pid, uint8_t eid) {
	asm volatile ("cli");

	if (_uik_tcb[pid].state == wait_event && _uik_tcb[pid].event == eid) {
		_uik_tcb[pid].state = ready;
	}

	asm volatile ("sei");

	return;
}

void uik_event_raise(uint8_t eid) {
	uint8_t i;

	asm volatile ("cli");

	for (i = 0; i < _uik_tasks_num; i++) {
		switch (_uik_tcb[i].state) {
			case wait_event:
				if (_uik_tcb[i].event == eid) {
					_uik_tcb[i].state = ready;
				}

			default:
				break;
		}
	}

	asm volatile ("sei");

	return;
}
