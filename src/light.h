#ifndef LIGHTING_H
#define LIGHTING_H

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

#include "./vector3.h"

#include "./shapes.h"
#include "./light.h"

typedef enum {
    LIGHT_POINT,
    LIGHT_DIRECTIONAL,
    LIGHT_AMBIENT,
} Light_Kind;

typedef struct Light {
    Vector3 Direction;
    float intensity;
    Light_Kind kind;
} Light;

Light *new_light(Vector3 Direction, Light_Kind kind, float intensity);
void free_light(Light *light);
Color color_intensity_mul(Color color, float intensity);
void light_prop(Light *light);
#endif /*LIGHTING_H*/
