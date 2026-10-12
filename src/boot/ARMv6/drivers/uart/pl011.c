#include "pl011.h"
#include "../etc/delay.h"

void pl011init() {
    mem32write(PL011_BASE + CR, 0);

    mem32write(PL011_BASE + IBRD, 26);
    mem32write(PL011_BASE + FBRD, 3);

    mem32write(PL011_BASE + LCRH, 1 << 4 | 3 << 5);

    mem32write(PL011_BASE + CR, 1 | 1 << 8 | 1 << 9);

    Delay(500);

    mem32write(PL011_BASE + LCRH, 1 << 4 | 3 << 5);
}

void pl011write(char c) {
    PL011Flags Flags = {0};
    Flags.Flags = mem32read(PL011_BASE + FR);

    // TX FIFO가 비어있는지 확인
    // BUSY가 아닌지도 확인
    while ((mem32read(PL011_BASE + FR) & (1 << 5)) != 0);
    mem32write(PL011_BASE + DR, c);
}

char pl011read() {
    while ((mem32read(PL011_BASE + FR) & (1 << 4)) != 0);
    return mem32read(PL011_BASE + DR);
}

void pl011enable() {

}
void pl011disable() {
    
}