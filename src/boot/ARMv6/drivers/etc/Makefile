.PHONY: all etc

root = ../../../../..

etc : delay.c string.c
	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c delay.c \
		-o $(root)/obj/boot/ARMv6/drivers/etc/delay.o

	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c string.c \
		-o $(root)/obj/boot/ARMv6/drivers/etc/string.o

	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c math.c \
		-o $(root)/obj/boot/ARMv6/drivers/etc/math.o