#include "delay.h"

void Delay(unsigned int Delay) {
    for (unsigned int i = 0; i < Delay; i++)
    {
        __asm__ __volatile__ ("nop");
    }
    
}