#include <stdint.h>

static void enable_port_clock(void);
static void configure_pin(void);
static void toggle_pin(void);

int
main(void)
{
	enable_port_clock();
	configure_pin();

	for (;;) {
		for (volatile uint32_t delay = 2000000; delay > 0; --delay){

		}

		toggle_pin();
	}

	return (0);
}

static void enable_port_clock(void)
{
	uint32_t rcc_base_addr = 0x40021000;
	uint32_t rcc_apb2enr_addr = rcc_base_addr + 0x18;

	uint32_t rcc_apb2enr_iopcen = 1 << 4;
	uint32_t* p_rcc_apb2enr_addr = (uint32_t*)rcc_apb2enr_addr;

	uint32_t rcc_apb2enr_value = *p_rcc_apb2enr_addr;
	rcc_apb2enr_value |= rcc_apb2enr_iopcen;

	*p_rcc_apb2enr_addr = rcc_apb2enr_value;
}

static void configure_pin(void)
{
	uint32_t pgioc_base_addr = 0x40011000;
	uint32_t gpioc_crh_addr = pgioc_base_addr + 0x04;
	
	uint32_t gpiox_crh_mode_13_0 = 1 << 20;
	uint32_t gpiox_crh_mode_13_1 = 1 << 21;
	uint32_t gpiox_crh_cnf_13_0 = 1 << 22;
	uint32_t gpiox_crh_cnf_13_1 = 1 << 23;

	uint32_t* p_gpioc_crh_addr = (uint32_t*)gpioc_crh_addr;
	uint32_t gpioc_crh_value = *p_gpioc_crh_addr;

	gpioc_crh_value &= ~gpiox_crh_mode_13_0;
	gpioc_crh_value |= gpiox_crh_mode_13_1;
	gpioc_crh_value |= gpiox_crh_cnf_13_0;
	gpioc_crh_value &= ~gpiox_crh_cnf_13_1;

	*p_gpioc_crh_addr = gpioc_crh_value;
}

static void toggle_pin(void)
{
	uint32_t gpioc_base_addr = 0x40011000;
	uint32_t gpioc_odr_addr = gpioc_base_addr + 0x0C;
	uint32_t gpiox_odr_odr13 = 1 << 13;

	uint32_t* p_gpioc_odr = (uint32_t*)gpioc_odr_addr;
	uint32_t gpioc_odr_value = *p_gpioc_odr;

	gpioc_odr_value ^= gpiox_odr_odr13;
	*p_gpioc_odr = gpioc_odr_value;
}