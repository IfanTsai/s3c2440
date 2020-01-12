#include "uart.h"

char g_a = 'A';
unsigned int g_b;
unsigned int g_c = 0;
unsigned int g_d = 0x11112222;

int main(void)
{
	uart_init();

	putc(g_a);
	puts("\n");
	put_hex(g_b);
	puts("\n");
	put_hex(g_c);
	puts("\n");
	put_hex(g_d);
	puts("\n");

	return 0;
}
