.global _start
.global main

.section .text
_start:
    LDR sp, =0x8000 // 커널 스택은 8KB로
    
    LDR r0, =0x0FFFC000 // 커널 영역
    LDR r1, =0x1FFFC000 // 유저 영역

    MCR p15, 0, r0, c2, c0, 0 // TRBR0에 커널 영역 등록
    MCR p15, 0, r1, c2, c0, 1 // TRBR1에 유저 영역 등록

    // TTBCR 얻고 N을 0으로 설정.
    MRC p15, 0, r0, c2, c0, 2 // TTBCR을 r0에
    AND r0, r0, #0xFFFFFFF8 // 앞 3비트 0으로 초기화
    ORR r0, r0, #0b011 // 2의 32-3 제곱인 512MB만 먹고 나머지는 유저 영역 주기.
    
    MCR p15, 0, r0, c2, c0, 2 // r0을 TTBCR에

    BL main

.:
    b .