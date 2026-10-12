typedef struct
{
    unsigned short Length;
    char* Pointer;
} string;

string* createstring(char* String);
void freestring(string* str);

char* stoc(string* s);
void itos(string* s, unsigned int i);
void htos(string* s, unsigned int i);