#ifndef VEC_H
#define VEC_H

typedef struct VEC_T {
    double x, y, z;
} VEC_T;

double dot(VEC_T v1, VEC_T v2);
VEC_T normalize(VEC_T v);

#endif
