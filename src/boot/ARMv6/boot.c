#include "drivers/memory/mmu.h"
#include "drivers/memory/memory.h"
#include "drivers/io/gpio.h"
#include "drivers/io/mmc.h"
#include "drivers/uart/uart.h"
#include "drivers/etc/string.h"

void start() {
    // RAM의 쓰레기 값들을 0으로 초기화.
    for (int i=0; i<0xB80000; i++) {
        ((volatile unsigned long long*)0x02800000)[i] = 0;
    }

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

    char* Heap1 = (char*)kmalloc(32);
    Heap1[0] = 'S';
    Heap1[1] = 'y';
    Heap1[2] = 'n';
    Heap1[3] = 't';
    Heap1[4] = 'h';
    Heap1[5] = 'e';
    Heap1[6] = 'i';
    Heap1[7] = 's';
    Heap1[8] = 'e';
    Heap1[9] = ' ';
    Heap1[10] = 'O';
    Heap1[11] = 'S';
    Heap1[12] = ' ';
    Heap1[13] = 'B';
    Heap1[14] = 'o';
    Heap1[15] = 'o';
    Heap1[16] = 't';
    Heap1[17] = 'l';
    Heap1[18] = 'o';
    Heap1[19] = 'a';
    Heap1[20] = 'd';
    Heap1[21] = 'e';
    Heap1[22] = 'r';
    Heap1[23] = ' ';
    Heap1[24] = '1';
    Heap1[25] = '.';
    Heap1[26] = '0';
    Heap1[27] = '.';
    Heap1[28] = '0';
    Heap1[29] = '\0';

    char* Text0 = (char*)kmalloc(16);
    char* Text1 = (char*)kmalloc(16);
    char* Text2 = (char*)kmalloc(16);
    char* Text3 = (char*)kmalloc(16);
    char* Text4 = (char*)kmalloc(16);
    string* str0 = createstring(Text0);
    string* str1 = createstring(Text1);
    string* str2 = createstring(Text2);
    string* str3 = createstring(Text3);
    string* str4 = createstring(Text4);

    uart_init();
    unsigned int* List = mmc_init();

    print_str(Heap1);
    print_c('\r'); 
    print_c('\n');
    htos(str0, List[0]);
    htos(str1, List[1]);
    htos(str2, List[2]);
    htos(str3, List[3]);
    htos(str4, List[4]);

    print_str(Text0);
    print_c('\r'); 
    print_c('\n');
    print_str(Text1);
    print_c('\r'); 
    print_c('\n');
    print_str(Text2);
    print_c('\r'); 
    print_c('\n');
    print_str(Text3);
    print_c('\r'); 
    print_c('\n');
    print_str(Text4);
    print_c('\r'); 
    print_c('\n');

    char* config = (char*)mmc_read(List[4], 0);
    print_str(config);

    /*int* a = kmalloc(20);
    int* b = kmalloc(20);
    
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;

    b[0] = 1;
    b[1] = 3;
    b[2] = 5;
    b[3] = 7;
    b[4] = 9;

    for (int i = 0; i<5; i++) {
        if (b[2] == a[i]) {
            print_c('1');
        } else if (b[2] > a[i]) {
            int s = 0;
            for (int n = 3; n<5; n++) {
                if (b[n] == a[i]) {
                    s = 1;
                    break;
                }
            }
            if (s == 1) {
                print_c('1');
            } else {
                print_c('0');
            }
        } else if (b[2] < a[1]) {
            int s = 0;
            for (int n = 1; n>-1; n--) {
                if (b[n] == a[i]) {
                    s = 1;
                    break;
                }
            }
            if (s == 1) {
                print_c('1');
            } else {
                print_c('0');
            }
        }
    }*/

    gpiomode(4, OUTPUT);
    gpiomode(17, OUTPUT);

    gpiomode(27, INPUT);
    gpioenable(4);
    //gpioenable(17);

    for (int i = 0; i<49999; i++);

    if (gpioread(27) == ENABLE) {
        gpioenable(17);
    }

    while (1) {

    }
}