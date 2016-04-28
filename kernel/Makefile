CC := avr-gcc
CFLAGS := -mmcu=atmega32 -Wall -Wextra -Wpedantic -DF_CPU=1000000UL -O2
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))

.PHONY : all clean

all : $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

defines.h : $(wildcard *.h)

clean :
	\rm -f $(OBJ)
