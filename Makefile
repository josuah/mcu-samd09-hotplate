CFLAGS = -Wall -Wextra -std=c99 -pedantic -ggdb
OBJ = arm32_aeabi_divmod.o arm32_aeabi_divmod_a32.o libc.o libsamd09.o \
	firmware.o font.o

all: firmware.elf firmware.asm

clean:
	rm -f *.o *.asm *.elf *.map *.hex

ocd:
	${OPENOCD}

gdb:
	${GDB} -x script.gdb

include libsamd09.mk
