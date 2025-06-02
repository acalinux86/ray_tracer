#ifndef LIGHTING_H
#define LIGHTING_H

#include "vector3.h"
#define FASIC_IMPLEMENTATION
#include "fasic.h"

typedef struct Light {
    Vector3 Direction;
} Light;

Light *Light_New(Vector3 Direction);
void Light_Free(Light *light);

#endif /*LIGHTING_H*/
