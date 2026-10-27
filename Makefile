all : ARMv6 X86

ARMv6_SRCDRIVERS = src/boot/ARMv6/drivers
ARMv6_OBJDRIVERS = obj/boot/ARMv6/drivers

ifeq ($(OS), Windows_NT)
ARMv6 : ARMv6_INIT ARMv6_BOOT
	copy "sdcard\*.*" F:\ /Y
else
ARMv6 : ARMv6_INIT ARMv6_BOOT
endif

ifeq ("$(wildcard obj/boot)", "")
ifeq ($(OS), Windows_NT)
ARMv6_INIT : 
	-mkdir bin
	-mkdir sdcard
	-mkdir sdcard\overlays

	-mkdir obj
	-mkdir obj\boot
	-mkdir obj\boot\ARMv6

	-mkdir obj\boot\ARMv6\drivers
	-mkdir obj\boot\ARMv6\drivers\io
	-mkdir obj\boot\ARMv6\drivers\memory
	-mkdir obj\boot\ARMv6\drivers\uart
	-mkdir obj\boot\ARMv6\drivers\etc
else
ARMv6_INIT :
	-mkdir bin
	-mkdir sdcard
	-mkdir sdcard/overlays

	-mkdir obj
	-mkdir obj/boot
	-mkdir obj/boot/ARMv6

	-mkdir obj/boot/ARMv6/drivers
	-mkdir obj/boot/ARMv6/drivers/io
	-mkdir obj/boot/ARMv6/drivers/memory
	-mkdir obj/boot/ARMv6/drivers/uart
	-mkdir obj/boot/ARMv6/drivers/etc
endif
else
ARMv6_INIT : 
endif

ARMv6_BOOT :
	make -C src/boot/ARMv6/drivers/memory
	make -C src/boot/ARMv6/drivers/io
	make -C src/boot/ARMv6/drivers/uart
	make -C src/boot/ARMv6/drivers/etc

	arm-none-eabi-gcc -mlittle-endian -mcpu=arm1176jzf-s -mfpu=vfpv2 -mfloat-abi=hard -nostdlib --sysroot=src/boot/ARMv6 -T linker.ld \
		src/boot/ARMv6/main.s src/boot/ARMv6/boot.c \
		$(ARMv6_OBJDRIVERS)/io/gpio.o $(ARMv6_OBJDRIVERS)/io/mmc.o \
		$(ARMv6_OBJDRIVERS)/memory/memory.o $(ARMv6_OBJDRIVERS)/memory/mmu.o \
		$(ARMv6_OBJDRIVERS)/uart/pl011.o $(ARMv6_OBJDRIVERS)/uart/mini.o $(ARMv6_OBJDRIVERS)/uart/uart.o \
		$(ARMv6_OBJDRIVERS)/etc/delay.o $(ARMv6_OBJDRIVERS)/etc/math.o $(ARMv6_OBJDRIVERS)/etc/string.o \
		-o sdcard/SBOOT.img -lgcc


X86 : X86_INIT X86_BOOT
	xorriso -as mkisofs -o "bin/Synthesise OS.iso" -iso-level 4 -r -J -eltorito-alt-boot -b boot/bios/boot -no-emul-boot -boot-load-size 8 -boot-info-table iso/

ifeq ("$(wildcard obj/boot/x86)", "")
ifeq ($(OS), Windows_NT)
X86_INIT :
	-mkdir obj\boot\x86
else
X86_INIT :
	-mkdir obj/boot/x86
endif
else
X86_INIT :
endif

X86_BOOT:
    # BIOS
	nasm -f bin src/boot/x86/bios/main.s -o iso/boot/bios/boot


ifeq ($(OS), Windows_NT)
clean:
	del obj\boot\ARMv6\*.* /F /Q
	del obj\boot\ARMv6\drivers\*.* /F /Q
	del obj\boot\ARMv6\drivers\io\*.* /F /Q
	del obj\boot\ARMv6\drivers\memory\*.* /F /Q
	del obj\boot\ARMv6\drivers\uart\*.* /F /Q
	del obj\boot\ARMv6\drivers\etc\*.* /F /Q
else
clean:
	rm --force obj\boot\ARMv6\*.*
	rm --force obj\boot\ARMv6\drivers\*.*
	rm --force obj\boot\ARMv6\drivers\io\*.*
	rm --force obj\boot\ARMv6\drivers\memory\*.*
	rm --force obj\boot\ARMv6\drivers\uart\*.*
	rm --force obj\boot\ARMv6\drivers\etc\*.*
endif
