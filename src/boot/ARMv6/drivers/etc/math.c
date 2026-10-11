#include "math.h"
unsigned int ipow(unsigned int x, unsigned int y) {
    unsigned int result = x;
    
    if (y < 2) {
        if (y == 0) {
            return 1;
        } else {
            return result;
        }
    } else {
        for (int i=1;i<y;i++) {
            result = result * x;
        }
    }

    return result;
}