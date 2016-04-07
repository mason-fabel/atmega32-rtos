#include <inttypes.h>
#include "defines.h"

uint8_t uik_task_add(uik_taskptr_t task, uint8_t priority, uint16_t stack_len) {
	return 0;
}

void uik_task_run(uint8_t pid) {
	return;
}

void uik_schedule(void) {
	return;
}

void _uik_task_idle(void) {
	while(1) {
		/* do nothing */
	}

	return;
}
