#include "math.h" //DO I NEED THIS
#include "light.h"

//FILL IN STUFF

//computes ambient, diffuse, and specular lighting; returns final color
COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, COLOR_T surface_col, VEC_T int_pt, VEC_T normal);
//returns true if int_point is in shadow
static int shadow_test (LIGHT_T light, OBJ_T *list, VEC_T int_pt);

