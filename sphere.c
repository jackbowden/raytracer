#include "math.h"
#include "sphere.h"

int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t);

//int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t, VEC_T *int_pt, VEC_T *normal);

//find out if the ray caster is looking at a sphere or not, attempt to return distance.
int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t) {
    VEC_T direction = ray.direction;
    VEC_T origin = ray.origin;
    VEC_T center = sphere.center;

    double b = 2 * ((direction.x * (origin.x - center.x)) + (direction.y * (origin.y - center.y)) + (direction.z * (origin.z - center.z)));
    double c = pow((origin.x - center.x), 2) + pow((origin.y - center.y), 2) + pow((origin.z - center.z), 2) - pow(sphere.radius, 2);
    double discrimnt = (b * b) - (4 * c);

    if (discrimnt < 0) {
        return 0;
    }

    double length = ((-b) + sqrt(discrimnt)) / 2;
    double length2 = ((-b) - sqrt(discrimnt)) / 2;
    if (length <= 0 && length2 <= 0) {
        return 0;
    }
    if (length <= 0 && length2 > 0) {
        *t = length2;
        return 1;
    }
    if (length > 0 && length2 <= 0) {
        *t = length;
        return 1;
    }
    if (length > 0 && length2 > 0) {
        if (length < length2) {
            *t = length;
            return 1;
        }
        else {
           *t = length2;
            return 1;
        }
    }
}
