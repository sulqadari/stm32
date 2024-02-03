#include <stdint.h>

static const uint32_t const_init_value_1 = 0x12345678;
static const uint32_t const_init_value_2 = 3;
static uint32_t init_value_3 = const_init_value_1;
static uint32_t uninit_value_4;

void
func_start(void)
{
	for (;;) {
		uninit_value_4 = init_value_3 + const_init_value_2;
		init_value_3 = uninit_value_4;
	}
}