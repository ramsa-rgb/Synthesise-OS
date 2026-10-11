#include "gpio.h"
#include "..\etc\delay.h"

void gpiomode(unsigned int gpio, unsigned int mode) {
    unsigned int base = 0;
    unsigned int offset = 0;

    if (gpio < 10) {
        // GPFSEL0
        offset = gpio*3;
        base = GPFSEL0;
    }
    else if (gpio >= 10 && gpio < 20)
    {
        // GPFSEL1
        offset = (gpio-10)*3;
        base = GPFSEL1;
    }
    else if (gpio >= 20 && gpio < 30)
    {
        // GPFSEL2
        offset = (gpio-20)*3;
        base = GPFSEL2;
    }
    else if (gpio >= 30 && gpio < 40)
    {
        // GPFSEL3
        offset = (gpio-30)*3;
        base = GPFSEL3;
    }

    unsigned int GPFSELn = mem32read(base);
    GPFSELn = GPFSELn & ~(0x7 << offset);
    mem32write(base, GPFSELn | (mode << offset));
}

void gpioenable(unsigned int gpio) {
    if (gpio < 32) {
        mem32write(GPSET0, (1 << gpio));
    } else {
        mem32write(GPSET1, (1 << (gpio-32)));
    }
}

void gpiodisable(unsigned int gpio) {
    if (gpio < 32) {
        mem32write(GPCLR0, (1 << gpio));
    } else {
        mem32write(GPCLR1, (1 << (gpio-32)));
    }
}

unsigned int gpioread(unsigned int gpio) {
    if (gpio < 32) {
        return (mem32read(GPLEV0) >> gpio) & (0x1);
    } else {
        return (mem32read(GPLEV1) >> (gpio-32)) & (0x1);
    }
}

void gpiopullsettings(unsigned short gpio, unsigned short Settings) {
    mem32write(GPPUD, Settings);
    Delay(150);

    if (gpio < 32) {
        mem32write(GPPUDCLK0, 1 << gpio);
    } else {
        mem32write(GPPUDCLK1, 1 << gpio);
    }

    Delay(150);
    mem32write(GPPUD, 0);
    mem32write(GPPUDCLK0, 0);
    mem32write(GPPUDCLK1, 0);
}