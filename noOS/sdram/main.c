#include "sdram.h"
#define GPFCON (*(volatile int *)0x56000050)
#define GPFDAT (*(volatile int *)0x56000054)

int main(void)
{
	sdram_init();

	/* GPF4 output */
	GPFCON &= ~(0x1 << 9);
	GPFCON |= (0x1 << 8);

	if (sdram_test() == 0)
		GPFDAT &= ~(0x1 << 4); /* led on */
	else
		GPFDAT |= (0x1 << 4); /* led off */


	return 0;
}
