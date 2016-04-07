#include "defines.h"

ISR_NAKED(TIMER1_COMPA_vect) {
	_uik_tick_num++;

	/* save context */
	/* switch context */
	/* restore context */
}
