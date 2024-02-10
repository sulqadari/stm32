#include <stdint.h>

#define RCC						  0x40021000
#define RCC_APB2ENR   (uint32_t*)(RCC + 0x18)	/* for enabling GPIOB. */
#define RCC_APB1ENR	  (uint32_t*)(RCC + 0x1C)	/* for enabling USART3. */

#define GPIOB					  0x40010C00
#define GPIOB_CRH	(uint32_t*)(GPIOB + 0x04)	/* GPIOB high config register. */

#define USART3					  0x40004800
#define USART3_SR  (uint32_t*)(USART3 + 0x00)	/* Status register. */
#define USART3_DR  (uint32_t*)(USART3 + 0x04)	/* Data register. */
#define USART3_BRR (uint32_t*)(USART3 + 0x08)	/* Baud rate register. */
#define USART3_CR1 (uint32_t*)(USART3 + 0x0C)	/* Control register 1. */

static void
enable_usart(void)
{
	/* Enable PORT B clock. */
	uint32_t rcc_apb2enr_value = *RCC_APB2ENR;
	rcc_apb2enr_value |= (1 << 3);
	*RCC_APB2ENR = rcc_apb2enr_value;

	/* Configure GPIOB10 as alternate function output push-pull 2MHz. */
	uint32_t gpiob_crh_value = *GPIOB_CRH;
	gpiob_crh_value &= ~(1 << 8);
	gpiob_crh_value |=  (1 << 9);
	gpiob_crh_value &= ~(1 << 10);
	gpiob_crh_value |=  (1 << 11);
	*GPIOB_CRH = gpiob_crh_value;

	/* Enable USART3 clock. */
	uint32_t rcc_apb1enr_value = *RCC_APB1ENR;
	rcc_apb1enr_value |= 1 << 18;
	*RCC_APB1ENR = rcc_apb1enr_value;

	/* set baud rate to 9600. */
	uint32_t usart3_brr_value = 0x00000341;
	*USART3_BRR = usart3_brr_value;

	/* Enable USART3 and transmitter. */
	uint32_t usart_cr1_value = *USART3_CR1;
	usart_cr1_value |= (1 << 13); /* Enable USART. */
	usart_cr1_value |= (1 << 3);  /* Enable transmitter. */
	*USART3_CR1 = usart_cr1_value;
}

static void
send_string(const char* data)
{
	char ch = 0;
	uint32_t usart3_sr_txe = (1 << 7);
	uint32_t usart3_sr_value;

	for (uint32_t i = 0; data[i] != '\0'; ++i) {
		ch = data[i];

		/* Wait until data is transferred to the shift register. */
		do {
			usart3_sr_value = *USART3_SR;
		} while ((usart3_sr_value & usart3_sr_txe) == 0);

		*USART3_DR = (uint32_t)ch & 0x000000FF;
	}
}

static void
send_hello(void)
{
	static char data[] = "counter: 0\r\n";
	static uint8_t counter = 0;
	counter = (counter + 1) % 10;
	*(data + 9) = counter + '0';
	send_string(data);
}

int
main(void)
{
	enable_usart();
	for (;;) {
		send_hello();
		for (volatile uint32_t counter = 0; counter < 1000000; ++counter){ }
	}
}