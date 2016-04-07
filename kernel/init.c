#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>
#include "defines.h"

void uik_initialize(uint16_t tick_len, uint8_t max_tasks) {
	cli();

	TCCR1A = _UIK_TIMER_MODE_CTC_A | _UIK_TIMER_MODE_NORMAL_PORT;
	TCCR1B = _UIK_TIMER_MODE_CTC_B | _UIK_TIMER_PRESCALER_1;

	TIMSK |= (0x01 << OCIE1A);

	TCNT1H = 0x00;
	TCNT1L = 0x00;

	OCR1A = tick_len;

	uik_task_add(_uik_task_idle, _UIK_TASK_PRIORITY_MIN, _UIK_TASK_STACK_MIN);

	sei();

	return;
}
