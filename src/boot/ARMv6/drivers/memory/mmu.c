#include "mmu.h"
#include "memory.h"

// Size는 MB 단위.
void CreateKernelPage(unsigned int VirtualAddress, unsigned int RealAddress, unsigned int Size) {
    unsigned int DefaultPage = 0;
    unsigned int StartEntryAddress = KERNEL_TABLE + (((VirtualAddress / 0x100000)) * 4); // 엔트리 한개 당 MB에 대응하기 때문에 이렇게 대입.
    
    /* KernelPageCount이 누적된 페이지 수, (VirtualAddress / 0x100000)가 페이지의 순서인데, 그것을 더해서 누적된 페이지 수 위에 페이지 순서가 오게 하고, 엔트리는 4바이트 이므로 더한것을 곱해 기준점을 만드는 것. */

    DefaultPage |= MMU_AP_KERNEL | MMU_CACHE_NORMAL | 2;

    for (int i = 0; i < Size; i++) {
        unsigned int Page = DefaultPage;
        Page = Page | ((RealAddress & 0xFFF00000) + i * 0x100000);

        mem32write(StartEntryAddress + (i * 4), Page);
    }
}

// Size는 MB 단위.
void CreateDevicePage(unsigned int VirtualAddress, unsigned int RealAddress, unsigned int Size) {
    unsigned int DefaultPage = 0;
    unsigned int StartEntryAddress = KERNEL_TABLE + (((VirtualAddress / 0x100000)) * 4); // 엔트리 한개 당 MB에 대응하기 때문에 이렇게 대입.
    
    /* KernelPageCount이 누적된 페이지 수, (VirtualAddress / 0x100000)가 페이지의 순서인데, 그것을 더해서 누적된 페이지 수 위에 페이지 순서가 오게 하고, 엔트리는 4바이트 이므로 더한것을 곱해 기준점을 만드는 것. */

    DefaultPage |= MMU_AP_KERNEL | MMU_CACHE_DEVICE | MMU_XN | 2;

    for (int i = 0; i < Size; i++) {
        unsigned int Page = DefaultPage;
        Page = Page | ((RealAddress & 0xFFF00000) + i * 0x100000);

        mem32write(StartEntryAddress + (i * 4), Page);
    }
}

void CreateUserPage(unsigned int VirtualAddress, unsigned int RealAddress, unsigned int Size) {
    unsigned int DefaultPage = 0;
    unsigned int StartEntryAddress = USER_TABLE + (((VirtualAddress / 0x100000)) * 4); // 엔트리 한개 당 MB에 대응하기 때문에 이렇게 대입.
    
    /* UserPageCount이 누적된 페이지 수, (VirtualAddress / 0x100000)가 페이지의 순서인데, 그것을 더해서 누적된 페이지 수 위에 페이지 순서가 오게 하고, 엔트리는 4바이트 이므로 더한것을 곱해 기준점을 만드는 것. */

    DefaultPage |= MMU_AP_USER | MMU_CACHE_NORMAL | 2;

    for (int i = 0; i < Size; i++) {
        unsigned int Page = DefaultPage;
        Page = Page | ((RealAddress & 0xFFF00000) + i * 0x100000);

        mem32write(StartEntryAddress + (i * 4), Page);
    }
}

void EnableMMU() {
    __asm__ __volatile__ (
        "LDR r0, =0x0\n"
        "MCR p15, 0, r0, c8, c7, 0\n" // MVA 초기화

        "MCR p15, 0, r0, c7, c7, 0\n" // 캐시 초기화 (명령어와 데이터)

        "LDR r0, =0x55555555\n"
        "MCR p15, 0, r0, c3, c0, 0\n" // 도메인 권한 설정

        "MRC p15, 0, r0, c1, c0, 0\n"
        "ORR r0, r0, #1\n"
        "MCR p15, 0, r0, c1, c0, 0\n" // MMU 활성화

        "MOV r0, #0\n"
        "MCR p15, 0, r0, c7, c5, 4\n" // 파이프라인 플러시
    );
}

void DisableMMU() {

}