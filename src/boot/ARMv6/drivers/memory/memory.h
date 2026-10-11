#ifndef MEM_H
#define MEM_H

#define MEMOFFSET 0x70000000
#define HeapBase 0x02800000

unsigned int mem32read(unsigned int Address);
unsigned short mem16read(unsigned int Address);
unsigned char mem8read(unsigned int Address);

void mem32write(unsigned int Address, unsigned int Data);
void mem16write(unsigned int Address, unsigned short Data);
void mem8write(unsigned int Address, unsigned char Data);

void kfree(unsigned int* Heap);
unsigned int* kmalloc(unsigned short Size);
unsigned short GetHeapSize(unsigned int* Heap);

#endif