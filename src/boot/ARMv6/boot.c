#include "drivers/memory/mmu.h"
#include "drivers/memory/memory.h"
#include "drivers/io/gpio.h"
#include "drivers/uart/mini.h"
#include "drivers/uart/pl011.h"
#include "drivers/uart/uart.h"
#include "drivers/etc/string.h"

void start() {
    // I/O 메모리는 32MB
    // 커널 영역은 8MB 크기
    CreateKernelPage(0x00000000, 0x00000000, 8); // Code
    CreateKernelPage(0x00800000, 0x00800000, 32); // Stack
    CreateKernelPage(0x02800000, 0x02800000, 184); // Heap
    CreateDevicePage(0x0E000000, 0x20000000, 16); // Device

    CreateUserPage(0x20000000, 0x10000000, 255); // User

    EnableMMU();
}
void main() {
    gpiomode(14, ALT0);
    gpiomode(15, ALT0);

    gpiopullsettings(14, PullDisable);
    gpiopullsettings(15, PullDisable);

    char* Heap1 = (char*)kmalloc(13);
    Heap1[0] = 'H';
    Heap1[1] = 'e';
    Heap1[2] = 'l';
    Heap1[3] = 'l';
    Heap1[4] = 'o';
    Heap1[5] = ' ';
    Heap1[6] = 'W';
    Heap1[7] = 'o';
    Heap1[8] = 'r';
    Heap1[9] = 'l';
    Heap1[10] = 'd';
    Heap1[11] = '!';
    Heap1[12] = '\0';

    char* Heap2 = (char*)kmalloc(13);
    Heap2[0] = 'H';
    Heap2[1] = 'e';
    Heap2[2] = 'l';
    Heap2[3] = 'l';
    Heap2[4] = 'o';
    Heap2[5] = ' ';
    Heap2[6] = 'A';
    Heap2[7] = 'r';
    Heap2[8] = 'm';
    Heap2[9] = 'v';
    Heap2[10] = '6';
    Heap2[11] = '!';
    Heap2[12] = '\0';

    char* heap3 = (char*)kmalloc(12);
    string* String = createstring(heap3);
    itos(String, (unsigned int)Heap1);

    uart_init();
    /*print_c('H');
    print_c('e');
    print_c('l');
    print_c('l');
    print_c('o');
    print_c(' ');
    print_c('W');
    print_c('o');
    print_c('r');
    print_c('l');
    print_c('d');
    print_c('!');
    print_c('\0');*/

    //print_str(Heap1);
    print_str(Heap2);
    print_str(stoc(String));

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