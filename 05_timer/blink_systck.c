#include <stdint.h>

static void enable_port_clock(void);
static void configure_pin(void);
static void toggle_pin(void);
static void configure_sys_tick_timer(void);

void
sys_tick_exception_handler(void)
{
	toggle_pin();
}

void
main(void)
{
	enable_port_clock();
	configure_pin();
	configure_sys_tick_timer();

	for (;;) { }
}

static void
enable_port_clock(void)
{
	uint32_t rcc_base_addr = 0x40021000;
	uint32_t rcc_apb2enr_addr = rcc_base_addr + 0x18;

	uint32_t rcc_apb2enr_iopcen = 1 << 4;
	uint32_t* p_rcc_apb2enr_addr = (uint32_t*)rcc_apb2enr_addr;

	uint32_t rcc_apb2enr_value = *p_rcc_apb2enr_addr;
	rcc_apb2enr_value |= rcc_apb2enr_iopcen;

	*p_rcc_apb2enr_addr = rcc_apb2enr_value;
}

static void
configure_pin(void)
{
	uint32_t base_addr = 0x40011000;
	uint32_t crh_addr = base_addr + 0x04;
	
	uint32_t crh_mode_13_0 = 1 << 20;
	uint32_t crh_mode_13_1 = 1 << 21;
	uint32_t crh_cnf_13_0 = 1 << 22;
	uint32_t crh_cnf_13_1 = 1 << 23;

	uint32_t* p_crh_addr = (uint32_t*)crh_addr;
	uint32_t crh_value = *p_crh_addr;

	crh_value &= ~crh_mode_13_0;
	crh_value |= crh_mode_13_1;
	crh_value |= crh_cnf_13_0;
	crh_value &= ~crh_cnf_13_1;

	*p_crh_addr = crh_value;
}

static void
toggle_pin(void)
{
	uint32_t gpioc_base_addr = 0x40011000;
	uint32_t gpioc_odr_addr = gpioc_base_addr + 0x0C;
	uint32_t gpiox_odr_odr13 = 1 << 13;

	uint32_t* p_gpioc_odr = (uint32_t*)gpioc_odr_addr;
	uint32_t gpioc_odr_value = *p_gpioc_odr;

	gpioc_odr_value ^= gpiox_odr_odr13;
	*p_gpioc_odr = gpioc_odr_value;
}

static void
configure_sys_tick_timer(void)
{
	uint32_t base_addr = 0xE000E010;
	uint32_t ctrl_addr = base_addr + 0x00;

	uint32_t ctrl_enable = 1 << 0;
	uint32_t ctrl_tickint = 1 << 1;

	uint32_t load_addr = base_addr + 0x04;

	// enable systick exception, enable systick counter
	volatile uint32_t* ctrl_pointer = (uint32_t*)ctrl_addr;
	uint32_t ctrl_value = *ctrl_pointer;

	ctrl_value |= ctrl_enable;
	ctrl_value |= ctrl_tickint;
	*ctrl_pointer = ctrl_value;

	// set reload value to 500 ms
	volatile uint32_t* load_pointer = (uint32_t*)load_addr;
	uint32_t load_value = 8000000 / 8;
	*load_pointer = load_value;
}