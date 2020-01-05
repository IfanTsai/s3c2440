#include "uart.h"

void delay()
{
	volatile int i = 1000000;
	while (i > 0)
		i--;
}

int main(void)
{
	uart_init();
	puts("\nhello world\n");
	char str[1024];
	while (1) {
		gets(str);
		puts(str);
		puts("\n");
	}
	return 0;
}
