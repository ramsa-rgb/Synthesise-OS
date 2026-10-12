#include "mmc.h"
#include "gpio.h"
#include "../memory/memory.h"
#include "../uart/uart.h"
#include "../etc/delay.h"

unsigned int* mmc_init() {
    gpiomode(48, ALT3);
    gpiomode(49, ALT3);
    gpiomode(50, ALT3);
    gpiomode(51, ALT3);
    gpiomode(52, ALT3);
    gpiomode(53, ALT3);

    // eMMC 리셋 요청
    mem32write(EMMC_BASE + CONTROL1, mem32read(EMMC_BASE + CONTROL1) | (1 << 24));
    while (((mem32read(EMMC_BASE + CONTROL1) >> 24) & 1) == 1);

    // 클럭 모드 정하기
    mem32write(EMMC_BASE + CONTROL1, mem32read(EMMC_BASE + CONTROL1) | (0 << 5) | (1 << 6) | (0x39 << 8) | 1);
    while (((mem32read(EMMC_BASE + CONTROL1) >> 1) & 1) == 0);

    // 나가는 클럭 활성화
    mem32write(EMMC_BASE + CONTROL1, mem32read(EMMC_BASE + CONTROL1) | (1 << 2));

    // 인터럽트 활성화 및 마스크
    mem32write(EMMC_BASE + IRPT_EN, 0xFFFFFFFF);
    mem32write(EMMC_BASE + IRPT_MASK, 0xFFFFFFFF);
    
    // GO_IDLE_STATE 보내기
    mem32write(EMMC_BASE + CMDTM, (0 << 24));
    while ((mem32read(EMMC_BASE + INTERRUPT) & 1) == 0);

    mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);
    
    // CMD55 & ACMD41 전압 조절 보내기.
    while (1) {
        mem32write(EMMC_BASE + ARG1, 0);
        mem32write(EMMC_BASE + CMDTM, 55 << 24 | 2 << 16);

        while ((mem32read(EMMC_BASE + INTERRUPT) & 1) == 0);

        mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

        // ACMD41
        mem32write(EMMC_BASE + ARG1, (0xFF80 << 8) | 1 << 30 | 1 << 31);
        mem32write(EMMC_BASE + CMDTM, 41 << 24 | 2 << 16);

        while ((mem32read(EMMC_BASE + INTERRUPT) & 1) == 0);

        mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

        if (mem32read(EMMC_BASE + RESP0) & (1 << 31)) {
            break;
        }
    }

    // CID 얻기
    unsigned int* List = kmalloc(20);

    mem32write(EMMC_BASE + ARG1, 0);
    mem32write(EMMC_BASE + CMDTM, 2 << 24 | 1 << 16);
    while ((mem32read(EMMC_BASE + INTERRUPT) & 1) == 0) {
        if (((mem32read(EMMC_BASE + INTERRUPT) >> 20) & 1) == 1) {
            mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

            mem32write(EMMC_BASE + ARG1, 0);
            mem32write(EMMC_BASE + CMDTM, 3 << 24 | 2 << 16);
        }
    }

    mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

    List[0] = mem32read(EMMC_BASE + RESP0);
    List[1] = mem32read(EMMC_BASE + RESP1);
    List[2] = mem32read(EMMC_BASE + RESP2);
    List[3] = mem32read(EMMC_BASE + RESP3);

    // RCA 얻기
    mem32write(EMMC_BASE + ARG1, 0);
    mem32write(EMMC_BASE + CMDTM, 3 << 24 | 2 << 16);
    while ((mem32read(EMMC_BASE + INTERRUPT) & 1) == 0) {
        if (((mem32read(EMMC_BASE + INTERRUPT) >> 20) & 1) == 1) {
            mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

            mem32write(EMMC_BASE + ARG1, 0);
            mem32write(EMMC_BASE + CMDTM, 3 << 24 | 2 << 16);
        }
    }

    mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

    List[4] = mem32read(EMMC_BASE + RESP0);

    // SD카드 선택
    mem32write(EMMC_BASE + ARG1, (List[4] >> 16) << 16);
    mem32write(EMMC_BASE + CMDTM, 7 << 24 | 3 << 16);
    while ((mem32read(EMMC_BASE + INTERRUPT) & 1) == 0) {
        if (((mem32read(EMMC_BASE + INTERRUPT) >> 20) & 1) == 1) {
            mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

            mem32write(EMMC_BASE + ARG1, (List[4] >> 16) << 16);
            mem32write(EMMC_BASE + CMDTM, 7 << 24 | 3 << 16);
        }
    }

    mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

    return List;
}

unsigned int* mmc_read(unsigned int Sector) {
    mem32write(EMMC_BASE + INTERRUPT, 0xFFFFFFFF);

    mem32write(EMMC_BASE + BLKSIZECNT, 512 | 1 << 16); // 블록 크기를 512bytes로
    mem32write(EMMC_BASE + ARG1, Sector);
    
}