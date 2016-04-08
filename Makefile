APPLICATION_NAME := avr-os
CC := avr-gcc
CFLAGS := -mmcu=atmega32 -Wall -Wextra -Wpedantic -O0
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))
KERNEL_SRC := $(wildcard kernel/*.c)
KERNEL_OBJ := $(patsubst %.c, %.o, $(KERNEL_SRC))

DEV := /dev/ttyS0

CLOCK_1MHz = 0xE1
CLOCK_2MHz = 0xE2
CLOCK_4MHz = 0xE3
CLOCK_8MHz = 0xE4

.PHONY : all install clean rebuild

all : $(APPLICATION_NAME)

install : $(APPLICATION_NAME)
	avrdude -q -q -p atmega32 -P $(DEV) -c stk500v2 \
		-U lfuse:w:$(CLOCK_1MHz):m \
		-U flash:w:$(APPLICATION_NAME).hex:i

$(APPLICATION_NAME) : $(OBJ) $(KERNEL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	objcopy -S -O ihex $(APPLICATION_NAME) $(APPLICATION_NAME).hex

$(OBJ) : $(SRC)

$(KERNEL_OBJ) : $(KERNEL_SRC)
	$(MAKE) -C kernel/

%.o : %.c
	$(CC) $(CFLAGS) -c $<

avr-os.c : kernel/kernel.h

clean :
	\rm -f $(APPLICATION_NAME) $(APPLICATION_NAME).hex $(OBJ)
	$(MAKE) clean -C kernel/

rebuild :
	make clean
	make all
