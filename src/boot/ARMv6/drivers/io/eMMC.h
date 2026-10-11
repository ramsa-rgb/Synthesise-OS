#ifndef EMMC_H
#define EMMC_H

#include "..\memory\memory.h"

#define EMMC_BASE 0x7E300000 - MEMOFFSET

#define ARG2 0x0
#define BLKSIZECNT 0x4
#define ARG1 0x08
#define CMDTM 0xc
#define RESP0 0x10
#define RESP1 0x14
#define RESP2 0x18
#define RESP3 0x1c
#define DATA 0x20
#define STATUS 0x24
#define CONTROL0 0x28
#define CONTROL1 0x2c
#define INTERRUPT 0x30
#define IRPT_MASK 0x34
#define IRPT_EN 0x38
#define CONTROL2 0x3c
#define FORCE_IRPT 0x50
#define BOOT_TIMEOUT 0x70
#define DBG_SEL 0x74
#define EXRDFIFO_CFG 0x80
#define EXRDFIFIO_EN 0x84
#define TUNE_STEP 0x88
#define TUNE_STEPS_STD 0x8c
#define TUNE_STEPS_DDR 0x90
#define SPI_INT_SOT 0xf0
#define SLOTISR_VER 0xfc

#endif