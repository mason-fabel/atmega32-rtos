CC := avr-gcc
CFLAGS := -mmcu=atmega32 -Wall -Wextra -Wpedantic -O0
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))

.PHONY : all clean

all : $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

%.c : %.h defines.h

defines.h : $(wildcard *.h)

clean :
	\rm -f $(OBJ)
