#include "./light.h"

Light *new_light(Vector3 Direction, Light_Kind kind, float intensity)
{
    Light *light = (Light *) malloc(sizeof(Light));
    if (light == NULL) {
        Log_Out(ERROR, "%s.\n", "Failed To Allocate Memory For Light");
        return NULL;
    }

    light->Direction = Direction;
    light->kind = kind;
    light->intensity = intensity;

    return light;
}

void free_light(Light *light)
{
    if (light) {
        UNLOAD(&light->Direction);
        free(light);
    }
}

// In color_intensity_mul() (ensure it clamps values):
Color color_intensity_mul(Color c, float intensity)
{
    return (Color){
        (uint8_t)fmin(255, c.r * intensity),
        (uint8_t)fmin(255, c.g * intensity),
        (uint8_t)fmin(255, c.b * intensity),
        255
    };
}
