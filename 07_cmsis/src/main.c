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

	/* Configure PB10 as alternate function output in push-pull mode 2MHz. */
	GPIOB->CRH &= ~GPIO_CRH_MODE10_0;
	GPIOB->CRH |=  GPIO_CRH_MODE10_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF10_0;
	GPIOB->CRH |=  GPIO_CRH_CNF10_1;

	/* Enable USAR3 clock. */
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	/* set baud rate. */
	USART3->BRR = 0x0341;
	/* enable USART3 and transmitter. */
	USART3->CR1 |= USART_CR1_UE;
	USART3->CR1 |= USART_CR1_TE;
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

		/* Write data to the data register. */
		USART3->DR = (uint32_t)ch & 0x000000FF;
	}
}

static void
send_message(void)
{
	static char data[] = "counter: 0\r\n";
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

