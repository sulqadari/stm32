.cpu cortex-m3
.syntax unified
.thumb

.global _reset_exception_handler

.section code

_reset_exception_handler:
	add r0, r0, 1
	bl _reset_exception_handler
