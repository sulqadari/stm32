#include <stdint.h>
#include "stm32f103xb.h"

void
__libc_init_array(void)
{
	/* Stub */
}

static void
enable_usart(void)
{
	/* Enable port B clock. */
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	uint32_t gpiob_crh = GPIOB->CRH;
	gpiob_crh &= ~GPIO_CRH_MODE10_0;
	gpiob_crh |=  GPIO_CRH_MODE10_1;
	gpiob_crh &= ~GPIO_CRH_CNF10_0;
	gpiob_crh |=  GPIO_CRH_CNF10_1;
	GPIOB->CRH = gpiob_crh;

	/* enable USAR3 clock. */
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	/* set baud rate. */
	USART3->BRR = 0x0341;

	/* enable USART3 and transmitter. */
	uint32_t usart3_cr1 = USART3->CR1;
	usart3_cr1 |= USART_CR1_UE;
	usart3_cr1 |= USART_CR1_TE;
	USART3->CR1 = usart3_cr1;
}

static void
enable_timer(void)
{
	SystemCoreClockUpdate();

	/* Enable systick exception and systick counter. */
	uint32_t systick_ctrl = SysTick->CTRL;
	systick_ctrl |= SysTick_CTRL_ENABLE_Msk;
	systick_ctrl |= SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL = systick_ctrl;

	/* Set reload value to 500 ms */
	SysTick->LOAD = SystemCoreClock / 8;
}


static void
send(const char* msg)
{
	char ch;
	for (uint32_t i = 0; msg[i] != '\0'; ++i) {

		ch = msg[i];

		/* wait until data is transferred to the shift register. */
		while ((USART3->SR & USART_SR_TXE) == 0) { }

		/* Write data to the dat aregister. */
		USART3->DR = (uint32_t)ch & 0x000000FF;
	}
}

static void
send_message(void)
{
	static char data[13] = "counter: 0\r\n";
	static uint8_t counter = 0;
	counter = (counter + 1) % 10;
	data[9] = counter + '0';
	send(data);
}

void
SysTick_Handler(void)
{
	send_message();
}

int
main(void)
{
	enable_usart();
	enable_timer();

	while (1) {

	}
}

