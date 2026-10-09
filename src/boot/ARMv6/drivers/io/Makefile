.PHONY: all io

root = ../../../../..

io : gpio.c
	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		$(root)/obj/boot/ARMv6/drivers/memory/memory.o \
		-c gpio.c \
		-o $(root)/obj/boot/ARMv6/drivers/io/gpio.o