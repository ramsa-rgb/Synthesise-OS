#ifndef MINI_H
#define MINI_H

#include "../memory/memory.h"

#define AUX_ENABLES 0x7E215004 - MEMOFFSET
#define AUX_MU_IO_REG 0x7E215040 - MEMOFFSET
#define AUX_MU_LCR_REG 0x7E21504C - MEMOFFSET
#define AUX_MU_MCR_REG 0x7E215050 - MEMOFFSET
#define AUX_MU_LSR_REG 0x7E215054 - MEMOFFSET
#define AUX_MU_MSR_REG 0x7E215058 - MEMOFFSET
#define AUX_MU_SCRATCH 0x7E21505C - MEMOFFSET
#define AUX_MU_CNTL_REG 0x7E215060 - MEMOFFSET
#define AUX_MU_STAT_REG 0x7E215064 - MEMOFFSET
#define AUX_MU_BAUD_REG 0x7E215068 - MEMOFFSET
#define AUX_MU_IIR_REG 0x7E215048  - MEMOFFSET

void minienable();
void minidisable();
void miniinit();
void miniwrite(char c);
char miniread();

#endif