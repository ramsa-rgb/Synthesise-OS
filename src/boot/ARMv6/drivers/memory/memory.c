#include "memory.h"

unsigned int mem32read(unsigned int Address) {
    unsigned int Data = *(volatile unsigned int*)Address;
    return Data;
}

void mem32write(unsigned int Address, unsigned int Data) {
    *(volatile unsigned int*)Address = Data;
}