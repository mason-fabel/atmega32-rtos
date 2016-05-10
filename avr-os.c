#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "kernel/kernel.h"

#define STACK_LEN 64
#define EVENT_BUTTON 1
#define SEM_UPDATE 1

volatile uint8_t val;
uint8_t stack_b[STACK_LEN] __attribute__((weak));
uint8_t stack_i[STACK_LEN] __attribute__((weak));
uint8_t stack_u[STACK_LEN] __attribute__((weak));

void init(void);
void task_button(void);
void task_increment(void);
void task_update(void);

int main(void) {
	init();

	uik_initialize(10);
	uik_sem_create(SEM_UPDATE, 0);
	uik_task_run(uik_task_add(task_button, 202, stack_b, STACK_LEN));
	uik_task_run(uik_task_add(task_increment, 201, stack_i, STACK_LEN));
	uik_task_run(uik_task_add(task_update, 200, stack_u, STACK_LEN));
	uik_run();

	return 0;
}

void init(void) {
	DDRA = 0x00;
	DDRB = 0xFF;

	PORTB = (uint8_t) ~0x80;
	_delay_ms(100);
	PORTB = (uint8_t) ~0x00;
	_delay_ms(100);

	val = 0;

	return;
}

void task_button(void) {
	while(1) {
		while (PINA == 0xFF) {
			/* wait for press */
		}

		uik_event_raise(EVENT_BUTTON);

		while (PINA != 0xFF) {
			/* wait for release */
		}
	}
	
	return;
}

void task_increment(void) {
	while(1) {
		uik_event_assoc(EVENT_BUTTON);
		val += 1;
		uik_sem_signal(SEM_UPDATE);
	}

	return;
}

void task_update(void) {

	while(1) {
		uik_sem_wait(SEM_UPDATE);
		PORTB = ~val;
	}

	return;
}
