OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
CPP = arm-none-eabi-cpp
CC = arm-none-eabi-gcc -mthumb -mcpu=cortex-m0plus -msoft-float
LD = arm-none-eabi-ld
AR = arm-none-eabi-ar
GDB = arm-none-eabi-gdb
OPENOCD = openocd -c 'set CPUTAPID 0x0bc11477' -f interface/stlink.cfg -f target/at91samdXX.cfg

flash: firmware.hex
	${OPENOCD} -c 'program firmware.hex verify reset exit'

firmware.elf: ${OBJ}
	${LD} -Map=firmware.map --gc-sections -Tlibsamd09.ld -nostdlib -static ${LDFLAGS} -o $@ ${OBJ}

.SUFFIXES: .c .s .S .o .elf .bin .asm .hex .uf2

.S.o:
	${CC} ${CPPFLAGS} ${CFLAGS} -c -o $@ $<

.c.o:
	${CC} ${CPPFLAGS} ${CFLAGS} -ffunction-sections -fdata-sections -c -o $@ $<

.elf.asm:
	${OBJDUMP} -z -d $< >$@

.elf.hex:
	${OBJCOPY} -j .text -j .data -O ihex $< $@
