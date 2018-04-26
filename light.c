#include "math.h" //DO I NEED THIS
#include "light.h"
#include "vec.h"

//computes ambient, diffuse, and specular lighting; returns final color
COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, COLOR_T surface_col, VEC_T int_pt, VEC_T normal)
{
    COLOR_T finished_color;
    finished_color = surface_col;

    VEC_T light_vector, r;
    double light_vector_normalized;
    light_vector.x = (light.loc.x - int_pt.x);
    light_vector.y = (light.loc.y - int_pt.y);
    light_vector.z = (light.loc.z - int_pt.z);
    light_vector_normalized = dot(normalize(light_vector), normal);


    //AMBIENT COLOR
    finished_color.R = 0.2 * surface_col.R;
    finished_color.G = 0.2 * surface_col.G;
    finished_color.B = 0.2 * surface_col.B;

    if (light_vector_normalized > 0)
    {
        //ADD SHADOW
        finished_color.R += light_vector_normalized * surface_col.R;
        finished_color.G += light_vector_normalized * surface_col.G;
        finished_color.B += light_vector_normalized * surface_col.B;

        //ADD SPECULAR
        r.x += light_vector.x - normal.x * 2 * light_vector_normalized;
        r.y += light_vector.y - normal.y * 2 * light_vector_normalized;
        r.z += light_vector.z - normal.z * 2 * light_vector_normalized;

        VEC_T r_normalized = normalize(r);
        if (dot(r_normalized, ray.direction) < 0) {
            finished_color.R += pow(dot(r_normalized, ray.direction), 200);
            finished_color.G += pow(dot(r_normalized, ray.direction), 200);
            finished_color.B += pow(dot(r_normalized, ray.direction), 200);
        }
    }


    return finished_color;

}
