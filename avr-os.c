#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "kernel/kernel.h"

#define STACK_LEN 64

void task_a(void);
void task_b(void);
void task_update(void);

uint8_t stack_a[STACK_LEN] __attribute__((weak));
uint8_t stack_b[STACK_LEN] __attribute__((weak));
uint8_t stack_update[STACK_LEN] __attribute__((weak));

uint8_t out;

int main(void) {
	DDRB = 0xFF;

	PORTB = (uint8_t) ~0x80;
	_delay_ms(100);
	PORTB = (uint8_t) ~0x00;
	_delay_ms(100);

	uik_initialize(100);

	out = 0x00;
	uik_task_run(uik_task_add(task_a, 100, stack_a, STACK_LEN));
	uik_task_run(uik_task_add(task_b, 100, stack_b, STACK_LEN));
	uik_task_run(uik_task_add(task_update, 101, stack_update, STACK_LEN));

	uik_run();

	while(1) PORTB = ~0x01;
}

void task_a(void) {
	uint8_t dat = 0;

	while (1) {
		dat = (dat + 1) % 16;
		out = (out & 0xF0) | dat;
		uik_delay(5000);
	}
}

void task_b(void) {
	uint8_t dat = 0;

	while (1) {
		dat = (dat + 1) % 16;
		out = (out & 0x0F) | (dat << 4);
		uik_delay(7500);
	}
}

void task_update(void) {
	while (1) {
		PORTB = ~out;
	}
}
