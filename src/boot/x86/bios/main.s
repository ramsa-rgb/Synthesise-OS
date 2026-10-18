[BITS 16]
[ORG 0x7c00]

section .text
_start:
  jmp 0x0000:boot
  times 8-($-$$) db 0

  ;	Boot Information Table
  bi_PrimaryVolumeDescriptor  resd  1    ; LBA of the Primary Volume Descriptor
  bi_BootFileLocation         resd  1    ; LBA of the Boot File
  bi_BootFileLength           resd  1    ; Length of the boot file in bytes
  bi_Checksum                 resd  1    ; 32 bit checksum
  bi_Reserved                 resb  40   ; Reserved 'for future standardization'

boot:
  mov si, Msg0
  call print

  jmp $

print:
  ; si가 Text의 주소
  push si
  push ax
  
  mov ah, 0x0e

  print.loop:
    mov bx, [si]

    cmp bl, 0
    jz print.loopend
    mov al, bl
    int 10h

    add si, 1

    cmp bl, 0
    jnz print.loop
  print.loopend:

  pop ax
  pop si
  ret

section .data
Msg0 db "Hello Synthesise OS!", 0

times 4096-($-$$) db 0