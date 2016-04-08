#ifndef _KERNEL_INIT_H_
#define _KERNEL_INIT_H_

#include <inttypes.h>

void _uik_init_kernel(uint8_t max_tasks);
void _uik_init_timer(uint16_t tick_len);

#endif /* _KERNEL_INIT_H_ */
