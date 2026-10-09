#include "memory.h"

unsigned int mem32read(unsigned int Address) {
    return *(volatile unsigned int*)Address;
}
unsigned short mem16read(unsigned int Address) {
    return *(volatile unsigned short*)Address;
}
unsigned char mem8read(unsigned int Address) {
    return *(volatile unsigned char*)Address;
}

void mem32write(unsigned int Address, unsigned int Data) {
    *(volatile unsigned int*)Address = Data;
}
void mem16write(unsigned int Address, unsigned short Data) {
    *(volatile unsigned short*)Address = Data;
}
void mem8write(unsigned int Address, unsigned char Data) {
    *(volatile unsigned char*)Address = Data;
}

void kfree(unsigned int Heap) {
    HeapBlock FirstHeap = {0};
    FirstHeap.Address = mem32read(Heap);
    FirstHeap.Size = mem32read(Heap+4);
    FirstHeap.NextHeapBlock = mem32read(Heap+8);
    FirstHeap.IsUse = 0;

    mem32write(Heap, FirstHeap.Address);
    mem32write(Heap+4, FirstHeap.Size);
    mem32write(Heap+8, FirstHeap.NextHeapBlock);
    mem32write(Heap+12, FirstHeap.IsUse);
}

unsigned int* kmalloc(unsigned int Size) {
    unsigned int heapcount = mem32read(0x027fffffc);
    HeapBlock NewHeapBlock = {0};
    NewHeapBlock.IsUse = 1;

    // Heap 구조

    // HeapBlock
    // Heap 데이터
    // ... 반복

    if (heapcount == 0) {
        NewHeapBlock.Address = HeapBase;
        NewHeapBlock.Size = Size;
        NewHeapBlock.NextHeapBlock = 0;
        
        mem32write(HeapBase, NewHeapBlock.Address);
        mem32write(HeapBase+4, NewHeapBlock.Size);
        mem32write(HeapBase+8, NewHeapBlock.NextHeapBlock);
        mem32write(HeapBase+12, NewHeapBlock.IsUse);

        for (int i = 0; i<Size; i++) {
            // 1바이트
            mem8write(HeapBase+4+i, 0);
        }
    } else {
        // 처음 구간을 찾음.
        HeapBlock FirstHeap = {0};
        FirstHeap.Address = mem32read(HeapBase);
        FirstHeap.Size = mem32read(HeapBase+4);
        FirstHeap.NextHeapBlock = mem32read(HeapBase+8);
        FirstHeap.IsUse = mem32read(HeapBase+12);

        if (FirstHeap.IsUse == 0) {
            // Free 됬다면 이 구간 사용.
            // 이 크기를 넘는다면 그 다음 빈 공간이 나올 때 까지 순회.
            if (FirstHeap.Size < Size) {

            } else {
                FirstHeap.IsUse = 1;

                mem32write(HeapBase, NewHeapBlock.Address);
                mem32write(HeapBase+4, NewHeapBlock.Size);
                mem32write(HeapBase+8, NewHeapBlock.NextHeapBlock);
                mem32write(HeapBase+12, NewHeapBlock.IsUse);
            }
        }
    }
}