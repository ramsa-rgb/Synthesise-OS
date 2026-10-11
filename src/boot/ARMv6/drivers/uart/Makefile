.PHONY: all uart

root = ../../../../..

uart : pl011.c mini.c
	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c pl011.c \
		-o $(root)/obj/boot/ARMv6/drivers/uart/pl011.o
	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c mini.c \
		-o $(root)/obj/boot/ARMv6/drivers/uart/mini.o
	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c uart.c \
		-o $(root)/obj/boot/ARMv6/drivers/uart/uart.o