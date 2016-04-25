#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "kernel/kernel.h"
#include "kernel/tick.h"

void init(void);
void task_a(void);
void task_b(void);

void init(void) {
	DDRA = 0x00;
	DDRB = 0xFF;

	PORTB = ~0x00;
	_delay_ms(100);
	PORTB = ~0x80;
	_delay_ms(100);
	PORTB = ~0x00;

	uik_initialize(100, 4);

/*
	uik_task_run(uik_task_add(task_a, 1, 64));
	uik_task_run(uik_task_add(task_b, 1, 64));
*/

	sei();

	return;
}

int main(void) {
	init();

	while (1) PORTB = ~0x01;

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
