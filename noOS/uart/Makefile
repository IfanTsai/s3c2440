CROSS_COMPILE = arm-linux-

CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS := -c -nostdlib -fno-builtin -std=c99

OBJ := uart.bin

.PRECIOUS: %.o %.elf
OBJS := $(patsubst %.S, %.o, $(wildcard *.S))
OBJS += $(patsubst %.c, %.o, $(wildcard *.c))

all: $(OBJ)

%.bin: %.elf
	$(OBJCOPY) -O binary -S $^ $@

%.elf: $(OBJS)
	$(LD) -Ttext 0x0000000 $^ -o $@

%.o: %.S
	$(CC) $(CFLAGS) -o $@ $< $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $< $(CFLAGS)

PHONY := clean
clean:
	-rm -f $(shell find -name "*.o")
	-rm -f $(shell find -name "*.elf")
	-rm -f $(shell find -name "*.bin")

PHONY += down
down:
	dnw $(OBJ)

.PHONY: $(PHONY)
