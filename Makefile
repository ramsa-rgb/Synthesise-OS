all : ARMv6

ARMv6_SRCDRIVERS = src/boot/ARMv6/drivers
ARMv6_OBJDRIVERS = obj/boot/ARMv6/drivers

ARMv6 : ARMv6_INIT ARMv6_BOOT
	copy sdcard\*.* F:

ARMv6_INIT : 
	-mkdir bin
	-mkdir sdcard
	-mkdir sdcard\overlays

	-mkdir obj\boot
	-mkdir obj\boot\ARMv6
	-mkdir obj\boot\ARMv6\x86
	-mkdir obj\boot\ARMv6\x86_64

	-mkdir obj\boot\ARMv6\drivers
	-mkdir obj\boot\ARMv6\drivers\io
	-mkdir obj\boot\ARMv6\drivers\memory
	-mkdir obj\boot\ARMv6\drivers\uart

ARMv6_BOOT :
	make -C src/boot/ARMv6/drivers/memory
	make -C src/boot/ARMv6/drivers/io

	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 \
		src/boot/ARMv6/main.s src/boot/ARMv6/boot.c \
		$(ARMv6_OBJDRIVERS)/io/gpio.o \
		$(ARMv6_OBJDRIVERS)/memory/memory.o $(ARMv6_OBJDRIVERS)/memory/mmu.o \
		-o obj/boot/ARMv6/SBOOT.img
	copy obj\boot\ARMv6\SBOOT.img sdcard /y

clean:
	del obj\boot\ARMv6\*.* /F /Q
	del obj\boot\ARMv6\drivers\*.* /F /Q
	del obj\boot\ARMv6\drivers\io\*.* /F /Q
	del obj\boot\ARMv6\drivers\memory\*.* /F /Q
	del obj\boot\ARMv6\drivers\uart\*.* /F /Q