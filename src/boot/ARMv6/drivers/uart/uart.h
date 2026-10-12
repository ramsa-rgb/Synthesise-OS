#ifndef UART_H
#define UART_H

#include "../memory/memory.h"

void uart_init();

void print_c(char c);
void print_str(char* c);

// 문자를 반환합니다.
char read_c();
// 받은 문자를 \0 까지 모아서 힙에 저장합니다.
char* read_str();
extern unsigned int UartMode;

#endif