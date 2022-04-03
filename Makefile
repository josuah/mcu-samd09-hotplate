CFLAGS = -Wall -Wextra -std=c99 -pedantic -ggdb
OBJ = firmware.o font.o
SDK = sdk
include ${SDK}/script.mk
flash: flash.openocd
