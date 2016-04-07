CC := avr-gcc
CFLAGS := -mmcu=atmega32 -Wall -Wextra -Wpedantic -DF_CPU=8000000UL -O2
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))

.PHONY : all clean

all : $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

dispatch.c : defines.h dispatch.h
idle.c : defines.h idle.h
init.c : defines.h
task.c : defines.h task.h
tick.c : defines.h tick.h

clean :
	\rm -f $(OBJ)
