#include "uart.h"

#include "mini.h"
#include "pl011.h"

// 0이면 Mini, 1이면 PL011.
unsigned int UartMode = 0;

void uart_init() {
    if (UartMode == 0) {
        miniinit();
    } else {
        pl011init();
    }
}

// 문자를 씁니다.
void print_c(char c) {
    if (UartMode == 0) {
        miniwrite(c);
    } else {
        pl011write(c);
    }
}
// 문자를 \0까지 씁니다.
void print_str(char* c) {
    int i = 0;
    while (1) {
        if (UartMode == 0) {
            miniwrite(c[i]);
        } else {
            pl011write(c[i]);
        }
        if (c[i] == '\0') {
            break;
        }
        i++;
    }
}

// 문자를 반환합니다.
char read_c() {
    if (UartMode == 0) {
        
    }
}
// 받은 문자를 \0 까지 모아서 힙에 저장합니다.
char* read_str() {
    if (UartMode == 0) {
        
    }
}