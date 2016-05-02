#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "kernel/kernel.h"

#define STACK_LEN 64

#define RATE_0 2000
#define RATE_1 3000
#define RATE_2 4000
#define RATE_3 5000
#define RATE_4 6000
#define RATE_5 7000
#define RATE_6 8000
#define RATE_7 9000

void task_led_0(void);
void task_led_1(void);
void task_led_2(void);
void task_led_3(void);
void task_led_4(void);
void task_led_5(void);
void task_led_6(void);
void task_led_7(void);
void task_update(void);

uint8_t stack_0[STACK_LEN] __attribute__((weak));
uint8_t stack_1[STACK_LEN] __attribute__((weak));
uint8_t stack_2[STACK_LEN] __attribute__((weak));
uint8_t stack_3[STACK_LEN] __attribute__((weak));
uint8_t stack_4[STACK_LEN] __attribute__((weak));
uint8_t stack_5[STACK_LEN] __attribute__((weak));
uint8_t stack_6[STACK_LEN] __attribute__((weak));
uint8_t stack_7[STACK_LEN] __attribute__((weak));
uint8_t stack_u[STACK_LEN] __attribute__((weak));

volatile uint8_t out;

int main(void) {
	DDRB = 0xFF;

	PORTB = (uint8_t) ~0x80;
	_delay_ms(100);
	PORTB = (uint8_t) ~0x00;
	_delay_ms(100);

	uik_initialize(10);

	out = 0x00;
	uik_task_run(uik_task_add(task_led_0, 107, stack_0, STACK_LEN));
	uik_task_run(uik_task_add(task_led_1, 106, stack_1, STACK_LEN));
	uik_task_run(uik_task_add(task_led_2, 105, stack_2, STACK_LEN));
	uik_task_run(uik_task_add(task_led_3, 104, stack_3, STACK_LEN));
	uik_task_run(uik_task_add(task_led_4, 103, stack_4, STACK_LEN));
	uik_task_run(uik_task_add(task_led_5, 102, stack_5, STACK_LEN));
	uik_task_run(uik_task_add(task_led_6, 101, stack_6, STACK_LEN));
	uik_task_run(uik_task_add(task_led_7, 100, stack_7, STACK_LEN));
	uik_task_run(uik_task_add(task_update, 200, stack_u, STACK_LEN));

	uik_run();

	return 0;
}

void task_led_0(void) {
	while (1) {
		out = out ^ 0x01;
		uik_delay(RATE_0);
	}
}

void task_led_1(void) {
	while (1) {
		out = out ^ 0x02;
		uik_delay(RATE_1);
	}
}

void task_led_2(void) {
	while (1) {
		out = out ^ 0x04;
		uik_delay(RATE_2);
	}
}

void task_led_3(void) {
	while (1) {
		out = out ^ 0x08;
		uik_delay(RATE_3);
	}
}

void task_led_4(void) {
	while (1) {
		out = out ^ 0x10;
		uik_delay(RATE_4);
	}
}

void task_led_5(void) {
	while (1) {
		out = out ^ 0x20;
		uik_delay(RATE_5);
	}
}

void task_led_6(void) {
	while (1) {
		out = out ^ 0x40;
		uik_delay(RATE_6);
	}
}

void task_led_7(void) {
	while (1) {
		out = out ^ 0x80;
		uik_delay(RATE_7);
	}
}

void task_update(void) {
	while(1) {
		PORTB = ~out;
		uik_delay(100);
	}
}
