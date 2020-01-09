#ifndef __SDRAM_H__
#define __SDRAM_H__

/* Bus width & wait status control register */
#define BWSCON    (*((volatile unsigned long *)0x48000000))
/* Bank 6 control register */
#define BANKCON6  (*((volatile unsigned long *)0x4800001C))
/* SDRAM refresh control register */
#define REFRESH   (*((volatile unsigned long *)0x48000024))
/* Flexible bank size register */
#define BANKSIZE  (*((volatile unsigned long *)0x48000028))
/* Mode register set register bank6 */
#define MRSRB6    (*((volatile unsigned long *)0x4800002C))

void sdram_init();
int sdram_test();

#endif