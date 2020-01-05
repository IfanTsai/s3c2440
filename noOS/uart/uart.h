#ifndef __UART_H__
#define __UART_H__

/* Configures the pins of port H */
#define GPHCON   (*((volatile unsigned long *)0x56000070))
/* pull-up disable register for port H */
#define GPHUP    (*((volatile unsigned long *)0x56000078))
/* UART channel 0 line control register */
#define ULCON0   (*((volatile unsigned long *)0x50000000))
/* UART channel 0 control register */
#define UCON0    (*((volatile unsigned long *)0x50000004))
/* UART channel 0 Tx/Rx status register */
#define UTRSTAT0 (*((volatile unsigned long *)0x50000010))
/* UART channel 0 transmit buffer register */
#define UTXH0    (*((volatile unsigned long *)0x50000020))
/* UART channel 0 receive buffer register */
#define URXH0    (*((volatile unsigned long *)0x50000024))
/* Baud rate divisior register 0 */
#define UBRDIV0	 (*((volatile unsigned long *)0x50000028))

void uart_init();
void puts(const char *s);
char *gets(char *s);

#endif
