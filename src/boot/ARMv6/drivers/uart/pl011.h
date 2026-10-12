#ifndef PL011_H
#define PL011_H

#include "../memory/memory.h"

#define PL011_BASE 0x7E201000 - MEMOFFSET

// 레지스터의 오프셋
#define DR 0x0
#define RSRECR 0x4
#define FR 0x18
#define ILPR 0x20
#define IBRD 0x24
#define FBRD 0x28
#define LCRH 0x2c
#define CR 0x30
#define IFLS 0x34
#define IMSC 0x38
#define RIS 0x3c
#define MIS 0x40
#define ICR 0x44
#define DMACR 0x48
#define ITCR 0x80
#define ITIP 0x84
#define ITOP 0x88
#define TDR 0x8c

typedef struct {
    unsigned int Flags;
} PL011Flags;

// dtoverlay=miniuart-bt 해야 작동.
void pl011enable();
void pl011disable();
void pl011init();
void pl011write(char c);
char pl011read();

#endif