//
// Created by Standardbenutzer on 01.04.2018.
//

#include <math.h>
#include "halton.h"

float halton(int base, int ix) {
    float r = 0;
    float f = 1.0f / base;
    int i = ix;
    while(i > 0) {
        r += f * (i % base);
        f /= base;
        i = (int)floorf((float)i / base);
    }

    return r;
}