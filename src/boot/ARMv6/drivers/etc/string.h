typedef struct
{
    unsigned short Length;
    unsigned int* Pointer;
} string;

string* createstring(char* String);

char* stoc(string* s);
void itos(string* s, unsigned int i);
