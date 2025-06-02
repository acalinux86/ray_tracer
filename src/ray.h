#ifndef RAY_H
#define RAY_H

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "fasic.h"

#include "vector3.h"
#include "shapes.h"

// Ray Structure and Information
typedef struct {
    Vector3 Origin;
    Vector3 Direction;
} Ray;

// Creates A New Ray
Ray *new_ray(Vector3 origin, Vector3 direction);

// Deallocates a dynamically allocated Ray Members
void free_ray(Ray *ray);

// Checks Whether a Ray has Intersected With a Sphere
bool RaySphereIntersection(Ray *ray, Sphere *sphere , float *t_min, float *t_max);
#endif /*RAY_H*/
