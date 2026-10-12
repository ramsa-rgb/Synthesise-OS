#include "mini.h"
#include "../memory/memory.h"

void miniinit() {
    mem32write(AUX_ENABLES, 1);
    mem32write(AUX_MU_CNTL_REG, 0);
    mem32write(AUX_MU_LCR_REG, 3);
    mem32write(AUX_MU_BAUD_REG, 270);
    mem32write(AUX_MU_IIR_REG, 0xC6);
    mem32write(AUX_MU_CNTL_REG, 3);
}

void miniwrite(char c) {
    while (((mem32read(AUX_MU_LSR_REG) >> 6) & 1) == 0);
    mem32write(AUX_MU_IO_REG, c);
}
char miniread() {
    while (((mem32read(AUX_MU_LSR_REG)) & 1) == 0);
    return mem32read(AUX_MU_IO_REG);
}

void minienable() {
    mem32write(AUX_ENABLES, 1);
}
void minidisable() {
    mem32write(AUX_ENABLES, 0);
}