#ifndef MMU_H
#define MMU_H

#define KERNEL_TABLE 0x0FFFC000
#define USER_TABLE 0x1FFFC000

#define MMU_NON_SECURE (1 << 19) // Secure 영역
#define MMU_XN (1 << 4) // 실행 방지

#define MMU_AP_KERNEL (1 << 10) // 커널 엑세스 권한
#define MMU_AP_USER (3 << 10) // 유저 엑세스 권한

#define MMU_CACHE_DEVICE (1 << 2) // 장치 캐시
#define MMU_CACHE_NORMAL (2 << 2) // 일반 캐시

// Size는 MB 단위.
void CreateKernelPage(unsigned int VirtualAddress, unsigned int RealAddress, unsigned int Size);
void CreateDevicePage(unsigned int VirtualAddress, unsigned int RealAddress, unsigned int Size);
void CreateUserPage(unsigned int VirtualAddress, unsigned int RealAddress, unsigned int Size);

void EnableMMU();
void DisableMMU();

#endif