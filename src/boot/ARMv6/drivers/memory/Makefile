.PHONY: all memory

root = ../../../../..

memory : memory.c mmu.c
	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c memory.c \
		-o $(root)/obj/boot/ARMv6/drivers/memory/memory.o
	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		-c mmu.c \
		-o $(root)/obj/boot/ARMv6/drivers/memory/mmu.o