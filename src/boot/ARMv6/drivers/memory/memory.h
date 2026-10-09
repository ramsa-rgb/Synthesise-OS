#ifndef MEM_H
#define MEM_H

#define MEMOFFSET 0x70000000

unsigned int mem32read(unsigned int Address);
void mem32write(unsigned int Address, unsigned int Data);

#endif