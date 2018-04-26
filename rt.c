/*
Jack Bowden
April 26, 2018
CSCI 304 Computer Organization
Professor Tim Davis
College of William & Mary

Ray caster program that accepts a text file where spheres, each one separated by new lines, are expected to be located and represented in a rendered .ppm image.
Improved to show objects in 3D!
*/

#include "rt.h"
#include "vec.h"
#include "obj.h"
#include "sphere.h"
#include "light.h"

#include "stdlib.h"
#include "stdio.h"
#include "math.h"

void read_objs(OBJ_T **list);

//reads objects from the given file into a list
void read_objs(OBJ_T **list) {
    double x, y, z, rad, r, g, b;
    *list = NULL;

    while (scanf("%lf %lf %lf %lf %lf %lf %lf", &x, &y, &z, &rad, &r, &g, &b) == 7) {
        OBJ_T *new_sphere = (OBJ_T *) malloc(sizeof(OBJ_T));
        new_sphere->sphere.center.x = x;
        new_sphere->sphere.center.y = y;
        new_sphere->sphere.center.z = z;
        new_sphere->sphere.radius = rad;
        new_sphere->color.R = r;
        new_sphere->color.G = g;
        new_sphere->color.B = b;

        new_sphere->next = *list;
        *list = new_sphere;
    }
}

//fire a ray and determine the color needed to represent what is being targeted
COLOR_T trace(RAY_T ray, OBJ_T *list, LIGHT_T light) {
    double distance;
    double minimum_distance = 1000.0;
    COLOR_T minimum_color, black, color;
    OBJ_T *pointer;
    OBJ_T *closest_obj = NULL;
    VEC_T int_pt, normal, closest_int_pt, closest_normal;

    black.R = 0.0;
    black.G = 0.0;
    black.B = 0.0;

    for (pointer = list; pointer != NULL; pointer = pointer->next) {
        distance = minimum_distance + 1.0;
        int sphere_located = intersect_sphere(ray, pointer->sphere, &distance, &int_pt, &normal);
        if (sphere_located == 1 && distance < minimum_distance) {
            minimum_distance = distance;
            minimum_color = pointer->color;
            closest_int_pt = int_pt;
            closest_normal = normal;
            closest_obj = pointer;
        }
    }

    if (closest_obj != NULL) {
        color = illuminate(ray, light, list, minimum_color, closest_int_pt, closest_normal);
        return color;
    }
    else {
        return black;
    }
}

/*
Reads all the spheres from the piped-in text file into a dynamic memory linked list.
Initializes the ppm image with the "magic number," the width and height of the image, and the max color value.
Traces rays upon the image space, painting colors and shaders to represent the spheres.
Free up everything at the very end.
*/
int main() {
    int x_pixel, y_pixel;

    OBJ_T *list;
    read_objs(&list);

    printf("P6\n");
    printf("1000 1000\n");
    printf("255\n");

    double z = 1;
    for (y_pixel = 0; y_pixel < 1000; y_pixel++) {
        for (x_pixel = 0; x_pixel < 1000; x_pixel++) {
            double x = -0.5 + (x_pixel / 1000.0);
            double y = 0.5 - (y_pixel / 1000.0);

            VEC_T target_location;
            target_location.x = x;
            target_location.y = y;
            target_location.z = z;
            target_location = normalize(target_location);

            RAY_T ray;
            VEC_T zero_vector;
            zero_vector.x = 0;
            zero_vector.y = 0;
            zero_vector.z = 0;
            ray.origin = zero_vector;
            ray.direction = target_location;

            LIGHT_T light;
            light.loc.x = 5;
            light.loc.y = 10;
            light.loc.z = 0;

            COLOR_T caps;
            caps.B = 1;
            caps.G = 1;
            caps.R = 1;

            COLOR_T color = trace(ray, list, light);
            if (color.R > caps.R) {
                color.R = 1;
            }
            if (color.G > caps.G) {
                color.G = 1;
            }
            if (color.B > caps.B) {
                color.B = 1;
            }
            unsigned char r = color.R * 255;
            unsigned char g = color.G * 255;
            unsigned char b = color.B * 255;

            printf("%c%c%c", r, g, b);
        }
    }

    OBJ_T *head;
    while (list != NULL) {
        head = list;
        list = list->next;
        free(head);
    }

    return 0;
}
