#ifndef SHAPES_H
#define SHAPES_H

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "fasic.h"

#include "vector3.h"

#define INITIAL_CAPACITY 64

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

typedef struct Sphere Sphere;

// Object Kinds
typedef enum {
    OBJECT_SPHERE,
    COUNT_OBJECT_KINDS,
} Object_Kind;

// Object Union
typedef union Object_Data {
    Sphere *sphere;
} Object_Data;

// Object Information
typedef struct Object {
    Object_Data object;
    Object_Kind kind;
} Object;

// Objects Array:
typedef struct Objects {
    Object *items;
    unsigned int count;
    unsigned int capacity;
} Objects;

// Spheres Begin:
struct Sphere {
    Vector3 position;
    float radius;
    Color color;
};

// Function Declarations:
bool compare_colors(Color a, Color b);
void free_objects(Objects *objs);
void insert_object(Objects *objs, Object *obj);
unsigned int search_object(Objects *objs, const Object *obj);
bool delete_object(Objects *objs, unsigned int index);
void pop_object(Objects *objs);
Object deep_copy_object(const Object *source);

Sphere *new_sphere(Vector3 position, float radius, Color color);
Object sphere_to_object(Sphere *sphere);
void free_sphere(Sphere *sphere);
Vector3 ComputeSurfaceNormal(Sphere *sphere, Vector3 intersectionPoint);


// TODO:
// Implement A Dynamic Array of shapes to be fed to the render func
// Add the array to the scene struct instead the sphere array

#endif /*SHAPES_H*/
