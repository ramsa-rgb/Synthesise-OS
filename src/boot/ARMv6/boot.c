#include "drivers/memory/mmu.h"
#include "drivers/memory/memory.h"
#include "drivers/io/gpio.h"

void main() {
    // I/O 메모리는 32MB
    // 커널 영역은 8MB 크기
    CreateKernelPage(0x00000000, 0x00000000, 8); // Code
    CreateKernelPage(0x00800000, 0x00800000, 32); // Stack
    CreateKernelPage(0x02800000, 0x02800000, 184); // Heap
    CreateDevicePage(0x0E000000, 0x20000000, 16); // Device

    CreateUserPage(0x20000000, 0x10000000, 255); // User

    EnableMMU();

    gpiomode(4, OUTPUT);
    gpiomode(17, OUTPUT);

    gpiomode(27, INPUT);
    gpioenable(4);
    //gpioenable(17);

    for (int i = 0; i<50000; i++);

    if (gpioread(27) == ENABLE) {
        gpioenable(17);
    }

    while (1) {

    }
}