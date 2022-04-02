CFLAGS = -Wall -Wextra -std=c99 -pedantic -ggdb
OBJ = firmware.o
SDK = sdk
include ${SDK}/script.mk
flash: flash.openocd
