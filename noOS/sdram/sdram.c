#include "sdram.h"

void sdram_init()
{
    /* Determines data bus width for bank 6: 32-bit */
    BWSCON |= (0x1 << 25);

    /* Determine the memory type for bank6: DRAM */
    /* Column address number: 9bit */
    BANKCON6 |= ((0x3 << 15) | (0x1 << 0));
    /* RAS to CAS delay: 2clocks = 2 * (1 / HCLK) = 20ns > 10ns */
    BANKCON6 &= ~(0x3 << 2);

    /* SDRAM Refresh Enable: Enable */
    REFRESH |= (0x1 << 23);
    /* SDRAM Refresh Mode: Auto Refresh */
    REFRESH &= ~(0x1 << 22);
    /* SDRAM RAS pre-charge Time: 2 clocks */
    REFRESH &= ~(0x3 << 20);
    /* SDRAM Semi Row cycle time: 5 clocks */
    REFRESH |= (0x1 << 18);
    REFRESH &= ~(0x1 << 19);
    /* SDRAM refresh count value */
    REFRESH |= (0x4F5 << 0);

    /* Enable burst operation */
    /* SDRAM power down mode enable */
    /* SCLK is active only during the access (recommended) */
    BANKSIZE |= ((0x1 << 7) | (0x1 << 5) | (0x1 << 4));
    /* BANK6/7 memory map: 64MB/64MB */
    BANKSIZE &= ~ (0x3 << 1);
    BANKSIZE |= (0x1 << 0);

    /* CAS latency: 2 clocks */
    MRSRB6 |= (0x2 << 4);
}

int sdram_test()
{
    volatile unsigned int *p = (volatile unsigned int *)(0x30000000);

    for (int i = 0; i < 1000; i++)
        p[i] = i;

    for (int i = 0; i < 1000; i++)
        if (p[i] != i)
            return -1;

    return 0;
}
