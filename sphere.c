#include "math.h"
#include "sphere.h"

//find out if the ray caster is looking at a sphere or not, attempt to return distance.
int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t, VEC_T *int_pt, VEC_T *normal) {
    VEC_T direction = ray.direction;
    VEC_T origin = ray.origin;
    VEC_T center = sphere.center;
    double radius = sphere.radius;

    double b = 2 * ((direction.x * (origin.x - center.x)) + (direction.y * (origin.y - center.y)) + (direction.z * (origin.z - center.z)));
    double c = pow((origin.x - center.x), 2) + pow((origin.y - center.y), 2) + pow((origin.z - center.z), 2) - pow(sphere.radius, 2);
    double discrimnt = (b * b) - (4 * c);

    if (discrimnt < 0) {
        return 0;
    }

    int_pt->x = origin.x + direction.x * *t;
    int_pt->y = origin.y + direction.y * *t;
    int_pt->z = origin.z + direction.z * *t;

    normal->x = (int_pt->x - center.x)/radius;
    normal->y = (int_pt->y - center.y)/radius;
    normal->z = (int_pt->z - center.z)/radius;

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
