.cpu cortex-m3
.syntax unified
.thumb

.global loop

.section code

loop:
	add r0, r0, 1	// increment value in r0
	bl loop			// loop back to the beginnig
