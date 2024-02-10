.cpu cortex-m3
.syntax unified
.thumb

.global loop
.section code

// 1. Turn on GPIOC
// 2. Configure PC13 as output in open drain collector mode
//    with maximum output speed 2 MHz

loop:
	// Enable clock in IO port C
	ldr r0, = 0x40021000 + 0x18	// assgin address of RCC_APB2ENR to r0
	ldr r1, [r0]				// load the value of RCC_APB2ENR into r1
								// More precisely, this line is almost equivalent
								// to: r1 = flash_memory_array[r0];

	orr r1, 1 << 4				// perform (RCC_APB2ENR | 0x04) on RCC_APB2ENR,
								// i.e. set IOPCEN bit
	str r1, [r0]				// store updated value of RCC_APB2ENR
								// this line is equivalent to:
								// flash_memory_array[r0] = r1;

	// Configure PC13. default value: CNF[0:1] MODE[0:0]
	//				   target  value: CNF[0:1] MODE[1:0]
	ldr r0, = 0x40011000 + 0x04	// assign the address of GPIOC_CRH to r0
	ldr r1, [r0]				// r1 = flash_memory_array[r0];
	bic r1, 1 << 20				// clear bit No 20
	orr r1, 1 << 21				// set bit	 No 21 (logical OR)
	orr r1, 1 << 22				// set bit	 No 21 (logical OR)
	bic r1, 1 << 23				// clear bit No 23
	str r1, [r0]				// flash_memory_array[r0] = r1;

	ldr r0, = 2000000			// assign 2,000,000 to r0
	delay:
		subs r0, 1
		bne delay

	ldr r0, = 0x40011000 + 0x0c	// GPIO_ODR
	ldr r1, [r0]
	eor r1, 1 << 13				// ODR13
	str r1, [r0]
	b loop
