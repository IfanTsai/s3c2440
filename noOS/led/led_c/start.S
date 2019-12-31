#define WTCON (0x53000000)

.global _start
_start:
	/* disable watchdog */
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]

	/* set stack address */
	ldr sp, =4*1024

	bl main

	b .
