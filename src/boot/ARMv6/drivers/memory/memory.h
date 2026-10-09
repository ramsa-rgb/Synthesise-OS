#ifndef MEM_H
#define MEM_H

#define MEMOFFSET 0x70000000
#define HeapBase 0x02800000

typedef struct
{
    unsigned int Address;
    unsigned int Size;
} Stack;

typedef struct
{
    unsigned int Address;
    unsigned int Size;
    unsigned int NextHeapBlock;
    unsigned int IsUse; // 1과, 0
} HeapBlock;

unsigned int mem32read(unsigned int Address);
unsigned short mem16read(unsigned int Address);
unsigned char mem8read(unsigned int Address);

void mem32write(unsigned int Address, unsigned int Data);
void mem16write(unsigned int Address, unsigned short Data);
void mem8write(unsigned int Address, unsigned char Data);

unsigned int* kmalloc(unsigned int Size);

#endif