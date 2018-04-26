#ifndef LIGHT_H
#define LIGHT_H

#include "vec.h"
#include "rt.h" //is this needed?
#include "obj.h"

typedef struct LIGHT_T {
    VEC_T loc;
} LIGHT_T;

//function prototype?
COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, COLOR_T surface_col, VEC_T int_pt, VEC_T normal);
static int shadow_test (LIGHT_T light, OBJ_T *list, VEC_T int_pt);

#endif
