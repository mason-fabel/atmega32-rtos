#include <avr/io.h>
#include <util/delay.h>
#include "kernel/kernel.h"

int main(void) {
	DDRB = 0xFF;

	PORTB = (uint8_t) ~0x80;
	_delay_ms(100);
	PORTB = (uint8_t) ~0x00;
	_delay_ms(100);

	uik_initialize(100);
	uik_run();

	while(1) PORTB = ~0x01;
}
