#ifndef GPIO_H
#define GPIO_H

#include "..\memory\memory.h"

#define GPFSEL0 0x7e200000 - MEMOFFSET
#define GPFSEL1 0x7e200004 - MEMOFFSET
#define GPFSEL2 0x7e200008 - MEMOFFSET
#define GPFSEL3 0x7e20000c - MEMOFFSET

#define GPSET0 0x7e20001c - MEMOFFSET
#define GPSET1 0x7e200020 - MEMOFFSET

#define GPCLR0 0x7e200028 - MEMOFFSET
#define GPCLR1 0x7e20002c - MEMOFFSET

#define GPLEV0 0x7e200034 - MEMOFFSET
#define GPLEV1 0x7e200038 - MEMOFFSET

#define INPUT 0b000
#define OUTPUT 0b001
#define AF0 0b100
#define AF1 0b101
#define AF2 0b110
#define AF3 0b111
#define AF4 0b011
#define AF5 0b010

#define ENABLE 1
#define DISABLE 0

void gpiomode(unsigned int gpio, unsigned int mode);
void gpioenable(unsigned int gpio);
void gpiodisable(unsigned int gpio);
unsigned int gpioread(unsigned int gpio);

#endif