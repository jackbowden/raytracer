#include "vec.h"
#include "sphere.h"

#ifndef OBJ_H
#define OBJ_H

typedef struct OBJ_T {
    SPHERE_T sphere;
    COLOR_T color;
    struct OBJ_T * next;
} OBJ_T;

#endif
