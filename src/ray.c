#include "./ray.h"

// Creates A New Ray
Ray *new_ray(Vector3 origin, Vector3 direction)
{
    Ray *ray = (Ray *) malloc(sizeof(Ray));
    if (ray == NULL) {
        Log_Out(ERROR, "%s.\n", "Failed To Allocate Memor For Ray");
        return NULL;
    }

    Vector3 direction_normalized = Vector3_Normalize(&direction);
    ray->Origin = origin;
    ray->Direction = direction_normalized;

    UNLOAD(&direction);
    return ray;
}

// Deallocates a dynamically allocated Ray Members
void free_ray(Ray *ray)
{
    if (ray) {
        UNLOAD(&ray->Direction);
        UNLOAD(&ray->Origin);
        free(ray);
    }
}

// Checks Whether a Ray has Intersected With a Sphere
bool RaySphereIntersection(Ray *ray, Sphere *sphere , float *t_min, float *t_max) {
    Vector3 oc = Vector3_Subtract(&ray->Origin, &sphere->position);
    float a = Vector3_Dot(&ray->Direction, &ray->Direction);
    float b = 2.0f * Vector3_Dot(&oc, &ray->Direction);
    float c = Vector3_Dot(&oc , &oc) - sphere->radius * sphere->radius;

    float discriminant = b*b - 4 * a * c;

    if (discriminant < 0) {
        UNLOAD(&oc); // Free oc on false return
        return false;
    }
    float t0 = (- b - sqrt(discriminant)) / (2.0f * a);
    float t1 = (- b + sqrt(discriminant)) / (2.0f * a);
    *t_min = t0;
    *t_max = t1;
    UNLOAD(&oc); // Free oc on true return
    return true;
}
