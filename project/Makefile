# makefile configuration
COMMON_OBJECTS	=
CPU	      	= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

# switch the compiler (for internal make rules)
CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: lab.elf

# additional rules for files
lab.elf: ${COMMON_OBJECTS} main.o stateMachines.o switches.o led.o buzzer.o p2_interrupt_handler.o wdInterruptHandler.o ../demos/lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: lab.elf
	msp430loader.sh lab.elf
clean:
	rm -f *.o *.elf

main.o: main.c

stateMachines.o: stateMachines.c stateMachines.h

switches.o: switches.c switches.h

led.o: led.c led.h

buzzer.o: buzzer.c buzzer.h

p2_interrupt_handler.o: p2_interrupt_handler.c

wdInterruptHandler.o: stateMachines.h led.h
