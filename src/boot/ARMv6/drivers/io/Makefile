.PHONY: all io

root = ../../../../..

io : gpio.c emmc.c
	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c gpio.c \
		-o $(root)/obj/boot/ARMv6/drivers/io/gpio.o

	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c emmc.c \
		-o $(root)/obj/boot/ARMv6/drivers/io/emmc.o