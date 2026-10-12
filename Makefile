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
	make -C src/boot/ARMv6/drivers/uart
	make -C src/boot/ARMv6/drivers/etc

	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 -T linker.ld \
		src/boot/ARMv6/main.s src/boot/ARMv6/boot.c \
		$(ARMv6_OBJDRIVERS)/io/gpio.o $(ARMv6_OBJDRIVERS)/io/emmc.o \
		$(ARMv6_OBJDRIVERS)/memory/memory.o $(ARMv6_OBJDRIVERS)/memory/mmu.o \
		$(ARMv6_OBJDRIVERS)/uart/pl011.o $(ARMv6_OBJDRIVERS)/uart/mini.o $(ARMv6_OBJDRIVERS)/uart/uart.o \
		$(ARMv6_OBJDRIVERS)/etc/delay.o $(ARMv6_OBJDRIVERS)/etc/math.o $(ARMv6_OBJDRIVERS)/etc/string.o \
		-o obj/boot/ARMv6/SBOOT.img -lgcc
	copy obj\boot\ARMv6\SBOOT.img sdcard /y

clean:
	del obj\boot\ARMv6\*.* /F /Q
	del obj\boot\ARMv6\drivers\*.* /F /Q
	del obj\boot\ARMv6\drivers\io\*.* /F /Q
	del obj\boot\ARMv6\drivers\memory\*.* /F /Q
	del obj\boot\ARMv6\drivers\uart\*.* /F /Q