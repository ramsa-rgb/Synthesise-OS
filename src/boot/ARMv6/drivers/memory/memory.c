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

void kfree(unsigned int* Heap) {
    unsigned int Meta = mem32read((unsigned int)Heap - 4);

    Meta &= 0xFFFEFFFF;

    mem32write((unsigned int)Heap - 4, Meta);
}

unsigned int* kmalloc(unsigned short Size) {
    // 맨 앞 힙 블록 읽기.
    // unsigned int MetaData;
    // 0:15 Size
    // 16:31 Flags

    unsigned int HeapPointer = HeapBase;
    unsigned int FirstMeta = 0;

    unsigned short HeapSize = 0;
    unsigned short HeapFlags = 0;

    while (1) {
        FirstMeta = mem32read(HeapPointer);

        HeapSize = (FirstMeta & 0xFFFF);
        HeapFlags = ((FirstMeta >> 16) & 0xFFFF);
        
        if (HeapSize == 0) {
            // 아무것도 없다면 여기에 HeapBlock 생성
            unsigned int Meta = 0;
            Meta |= Size;
            Meta |= (1 << 16);

            mem32write(HeapPointer, Meta);

            return (unsigned int*)(HeapPointer + 4); // 진짜 데이터만 반환.
        } else {
            // 있다면 쓰고 있는지 확인
            if ((HeapFlags & 1) == 0) {
                // 안쓰고 있다면
                // 메타데이터 포함
                if (HeapSize >= (Size + 4)) {
                    // 남은 공간이 크다면
                    // 남은 공간이 크고, 이 힙 데이터가 들어가고 남은 데이터가 8바이트이라면
                    if ((HeapSize - (Size + 4)) >= 8) {
                        // 크다면 작은 새 공간 창출.

                        // 먼저 요청한 힙
                        unsigned int Meta = 0;
                        Meta |= Size;
                        Meta |= (1 << 16);

                        mem32write(HeapPointer, Meta);

                        // 새 힙
                        unsigned int BMeta = 0;
                        BMeta |= (HeapSize - Size) - 4;
                        BMeta |= (0 << 16);

                        mem32write(HeapPointer + Size + 4, BMeta);                        

                        return (unsigned int*)(HeapPointer + 4); // 진짜 데이터만 반환.
                    } else {
                        // 작다면 이 힙이 다 먹기
                        unsigned int Meta = 0;
                        Meta |= HeapSize;
                        Meta |= (1 << 16);

                        mem32write(HeapPointer, Meta);

                        return (unsigned int*)(HeapPointer + 4); // 진짜 데이터만 반환.
                    }
                } else {
                    // 다음 블록
                    HeapPointer += HeapSize + 4;
                }
            } else {
                // 쓰고 있다면
                HeapPointer += HeapSize + 4;
            }
        }
    }
}

unsigned short GetHeapSize(unsigned int* Heap) {
    return (unsigned short)(mem32read((unsigned int)Heap - 4) & 0xFFFF);
}