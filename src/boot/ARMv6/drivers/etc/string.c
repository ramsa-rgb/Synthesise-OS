#include "string.h"
#include "math.h"
#include "..\memory\memory.h"

// String는 항상 kmalloc된 상태 이어야 합니다.
string* createstring(char* String) {
    unsigned short Size = GetHeapSize((unsigned int*)String);
    string* mstring = (string*)kmalloc(4);
    mstring->Length = Size;
    mstring->Pointer = (unsigned int*)String;

    return mstring;
}

char* stoc(string* s) {
    return (char*)s->Pointer;
}

// string의 길이는 12 이상이어야 합니다.
void itos(string* s, unsigned int i) {
    if (s->Length < 12) {
        return;
    }
    for (int n=0; n<=10; n++) {
        // i가 자릿수.
        
        // (i % 10) / 1
        // (i % x) / y

        unsigned int x = ipow(10, n+1);
        unsigned int y = ipow(10, n);

        char number = (i % x) / y;

        ((char*)s->Pointer)[n] = '0' + number;
    }
    
    ((char*)s->Pointer)[11] = '\0';
}