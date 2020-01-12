#define WTCON	 (0x53000000)
#define LOCKTIME (0x4c000000)
#define MPLLCON  (0x4c000004)
#define CLKDIVN  (0x4c000014)

.global _start
_start:
	/* disable watchdog */
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]

	/* clock initialization */
	bl clock_init

	/* set stack address for sram */
	ldr sp, =4*1024

	/* sdram initializtion */
	bl sdram_init

    adr r0, _start    /* run address */
    ldr r1, =_start   /* link address */
    ldr r2, =__bss_start
    cmp r0, r1
    beq clean_bss

	/* relocate */
relocate_loop:
    ldr r3, [r0], #4
    str r3, [r1], #4
    cmp r1, r2
    bne relocate_loop

	/* clean bss */
clean_bss:
    ldr r0, =__bss_start
    ldr r1, =__bss_end
	cmp r0, r1
	beq skip_clan_bss    /* if bss section is empty, skip clean_bss */
    mov r2, #0
clean_loop:
    str r2, [r0], #4
    cmp r0, r1
    bne clean_loop

skip_clan_bss:
	/* set stack address for sdram */
	ldr sp, =0x33000000

	bl main

	b .

clock_init:
	/* set PLL lock time count */
	ldr r0, =LOCKTIME
	ldr r1, =0xffffffff   /* default value */
	str r1, [r0]

	/*
	 * m = MDIV + 8 = 92 + 8 = 100
	 * p = PDIV + 2 =  1 + 2 = 3
	 * s = SDIV = 1
	 * Fin = 12MHz
	 * FCLK = Mpll = (2 * m * Fin) / (p * (2 ^ s))
	 *             = 2400 / 6
	 *             = 400MHz
	 */
	ldr r0, =MPLLCON
	/* MDIV[19:12]  PDIV[9:4]  SDIV[1:0] */
	ldr r1, =(92 << 12) | (1 << 4) | (1 << 0)
	str r1, [r0]

	/*
	 * HCLK = PCLK / 4 = 400HHz / 4 = 100MHz
	 * PCLK = HCLK / 2 = 100MHz / 2 = 50MHz
	 */
	ldr r0, =CLKDIVN
	/* HDIV[2:1]  PDIV[0] */
	ldr r1, =(0x2 << 1) | (0x1 << 0)
	str r1, [r0]

	/*
	 * MMU_SetAsyncBusMode
	 * If HDIVN is not 0 and the CPU bus mode is the fast bus mode,
	 * the CPU will operate by the HCLK
	 */
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0xc0000000         // #R1_nF:OR:R1_iA
	mcr p15, 0, r0, c1, c0, 0

	mov pc, lr
