#define WTCON  (0x53000000)
#define GPFCON (0x56000050)
#define GPFDAT (GPFCON + 0x4)

.global _start
_start:
	/* disable watchdog */
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]

	ldr r0, =GPFCON
	ldr r1, =(0x1 << 8)   /* GPF4(led) output, GPF0(key) input */
	str r1, [r0]

	ldr r0, =GPFDAT
	ldr r1, =~(0x1 << 4)
	ldr r2, =(0x1 << 4)

	bl led_off
	bl delay
key_loop:
	ldr r3, [r0]
	tst r3, #0x1
	ble led_on    /* if key down, led on */
	blne led_off  /* if key up, led off */
	b key_loop

led_on:
	str r1, [r0]
	mov pc, lr

led_off:
	str r2, [r0]
	mov pc, lr

delay:
	ldr r3, =100000
	ldr r4, =0
delay_loop:
	sub r3, r3, #1
	cmp r3, r4
	bne delay_loop
	mov pc, lr
