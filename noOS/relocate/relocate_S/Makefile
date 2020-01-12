CROSS_COMPILE = arm-linux-

CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS := -c -nostdlib -std=c99 -fno-builtin

OBJ := relocate.bin

.PRECIOUS: %.o %.elf
OBJS := $(patsubst %.S, %.o, $(wildcard *.S))
OBJS += $(patsubst %.c, %.o, $(wildcard *.c))

all: $(OBJ)

%.bin: %.elf
	$(OBJCOPY) -O binary -S $^ $@

%.elf: $(OBJS)
	$(LD) -Tlink.lds $^ -o $@

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
