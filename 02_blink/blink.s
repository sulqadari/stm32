.cpu cortex-m3
.syntax unified
.thumb

.global loop
.section code

// 1. Turn on GPIOC
// 2. Configure PC13 as output in open drain collector mode
// with maximum output speed 2 MHz
loop:
	// Enable clock in IO port C
	ldr r0, =0x40021000 + 0x18	// load address of RCC_APB2ENR to r0
	ldr r1, [r0]				// load r0 to r1, i.e. copy
	orr r1, 1 << 4				// (RCC_APB2ENR | 0x04), i.e. set IOPCEN bit
	str r1, [r0]				// store updated value of RCC_APB2ENR

	// Configure PC13. default value: CNF[0:1] MODE[0:0]
	//				   target  value: CNF[0:1] MODE[1:0]
	ldr r0, =0x40011000 + 0x04	// load address of GPIO Port C to r0
	ldr r1, [r0]				// load r0 to r1, i.e. copy
	bic r1, 1 << 20				// clear bit No 20
	orr r1, 1<< 21				// set bit	 No 21 (logical OR)
	orr r1, 1<< 22				// set bit	 No 21 (logical OR)
	bic r1, 1<< 23				// clear bit No 23
	str r1, [r0]				// store updated value of GPIO Port C

	ldr r0, =2000000		// assign 1,000,000 to r0
	delay:
		subs r0, 1
		bne delay
	ldr r0, =0x40011000 + 0x0c	// GPIO_ODR
	ldr r1, [r0]
	eor r1, 1 << 13				// ODR13
	str r1, [r0]
	b loop
