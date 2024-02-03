.cpu cortex-m3
.syntax unified
.thumb

.global loop

.section code

loop:
	add r0, r0, 1
	bl loop
