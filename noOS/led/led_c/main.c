#define GPFCON (*(volatile int *)0x56000050)
#define GPFDAT (*(volatile int *)0x56000054)

void delay()
{
	volatile int i = 100000;
	while (i > 0)
		i--;
}

int main(void)
{
	/* GPF4 output */
	GPFCON &= ~(0x1 << 9);
	GPFCON |= (0x1 << 8);

	while (1) {
		GPFDAT &= ~(0x1 << 4); /* led on */
		delay();
		GPFDAT |= (0x1 << 4); /* led off */
		delay();
	}

	return 0;
}
