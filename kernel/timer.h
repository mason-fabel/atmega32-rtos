#ifndef _UIK_TIMER_H_
#define _UIK_TIMER_H_

#include <avr/io.h>

#define _UIK_TIMER_MODE_CTC_A ((0x0 << WGM11) | (0x0 << WGM10))
#define _UIK_TIMER_MODE_CTC_B ((0x0 << WGM13) | (0x1 << WGM12))
#define _UIK_TIMER_MODE_NORMAL_PORT ((0x0 << COM1A1) | (0x0 << COM1A0))
#define _UIK_TIMER_PRESCALER_MASK ((1<<CS02)|(1<<CS01)|(1<<CS00))
#define _UIK_TIMER_PRESCALER_NONE ((0<<CS02)|(0<<CS01)|(0<<CS00))
#define _UIK_TIMER_PRESCALER_1    ((0<<CS02)|(0<<CS01)|(1<<CS00))
#define _UIK_TIMER_PRESCALER_8    ((0<<CS02)|(1<<CS01)|(0<<CS00))
#define _UIK_TIMER_PRESCALER_64   ((0<<CS02)|(1<<CS01)|(1<<CS00))
#define _UIK_TIMER_PRESCALER_256  ((1<<CS02)|(0<<CS01)|(0<<CS00))
#define _UIK_TIMER_PRESCALER_1024 ((1<<CS02)|(0<<CS01)|(1<<CS00))

#endif /* _UIK_TIMER_H_ */
