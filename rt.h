#ifndef RT_H
#define RT_H

#include "vec.h"

typedef struct RAY_T {
    VEC_T origin;
    VEC_T direction;
} RAY_T;

typedef struct COLOR_T {
    double R, G, B;
} COLOR_T;

#endif
