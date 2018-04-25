#include "math.h"
#include "vec.h"

VEC_T normalize(VEC_T v);
double dot(VEC_T v1, VEC_T v2);

VEC_T normalize(VEC_T v) {
    double length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    VEC_T normalized_v;
    normalized_v.x = v.x / length;
    normalized_v.y = v.y / length;
    normalized_v.z = v.z / length;
    return normalized_v;
}

double dot(VEC_T v1, VEC_T v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}
