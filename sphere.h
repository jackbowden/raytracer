#ifndef SPHERE_H
#define SPHERE_H

#include "vec.h"
#include "rt.h"

typedef struct SPHERE_T {
    VEC_T center;
    double radius;
} SPHERE_T;

int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t);

#endif
