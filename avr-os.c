#include <avr/interrupt.h>
#include <stdlib.h>
#include "kernel/kernel.h"

uint8_t pid_a;
uint8_t pid_b;

int init(void);
void task_a(void);
void task_b(void);

int init(void) {
	int status = 0;

	uik_initialize(100, 4);

	if(!(pid_a = uik_task_add(task_a, 1, 300))) {
		status = -1;
	}

	if(!(pid_b = uik_task_add(task_b, 2, 300))) {
		status = -1;
	}

	return status;
}

int main(void) {
	if (init()) {
		exit(-1);
	}

	uik_task_run(pid_a);
	uik_task_run(pid_b);

	while (1) {
		/* do nothing */
	}

	exit(0);
}

void task_a(void) {
	while (1) {
		/* do nothing */
	}

	return;
}

void task_b(void) {
	while (1) {
		/* do nothing */
	}

	return;
}
