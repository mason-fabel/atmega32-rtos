#ifndef _KERNEL_TICK_H_
#define _KERNEL_TICK_H_

#include <inttypes.h>

uint8_t _uik_tick_len;
uint32_t _uik_tick_num;

void _uik_dispatch(void);

#endif /* _KERNEL_TICK_H_ */
