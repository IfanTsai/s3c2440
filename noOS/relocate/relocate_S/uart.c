#include "uart.h"

/* 115200,8n,1 */
void uart_init()
{
	/* set GPH2,GPH3 is TXD[0],RXD[0] */
	GPHCON &= ~((0x3 << 4) | (0x3 << 6));
	GPHCON |= ((0x2 << 4) | (0x2 << 6));
	/* pull up GPH2 and GPH3 */
	GPHUP &= ~((0x1 << 2) | (0x1 << 3));
	/* 8-bits per frame, 1 stop bit */
	ULCON0 |= (0x3 << 0);
	/*
	 * Clock Selection: PCLK
	 * Transmit and Receive Mode: Interrupt request or polling mode
	 */
	UCON0 |= ((0x1 << 0) | (0x1 << 2));
	/*
	 * UBRDIVn = (int)( UART clock / ( buad rate * 16) ) –1
	 *         = (int)(50M / (115200 * 16)) - 1
	 *         = 26
	 */
	UBRDIV0 = 26;
}

void putc(char c)
{
	while (!(UTRSTAT0 & (0x1 << 2)));
	UTXH0 = c;
}

static char getc()
{
	while (!(UTRSTAT0 & (0x1 << 0)));
	return URXH0;
}

void puts(const char *s)
{
	while (*s) {
		if (*s == '\n')
			putc('\r');
		putc(*s++);
	}
}

char *gets(char *s)
{
	char *ts = s;
	char c;
	while ((c = getc()) != '\r') {
		if (c != '\b') {
			*s++ = c;
			/* echo input */
			putc(c);
		} else {
			/* when the user enters the backspace key, the output will go back */
			puts("\b \b");
			s--;
		}
	}
	*s = 0;

	if (c == '\r')
		puts("\r\n");

	return ts;
}

void put_hex(unsigned int val)
{
	unsigned char arr[8];

	for (int i = 0; i < 8; i++) {
		arr[i] = val & 0xf;
		val >>= 4;
	}

	puts("0X");
	for (int i = 7; i >= 0; i--)
		putc(arr[i] + (arr[i] >= 0 && arr[i] <= 9 ? '0' : 'A'));

}