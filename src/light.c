#include "light.h"

Light *Light_New(Vector3 Direction)
{
    Light *light = (Light *) malloc(sizeof(Light));
    if (light == NULL) {
        Log_Out(ERROR, "%s.\n", "Failed To Allocate Memory For Light");
        return NULL;
    }

    Vector3 Direction_Normalized = Vector3_Normalize(&Direction);
    light->Direction = Direction_Normalized;

    UNLOAD(&Direction);
    return light;
}

void Light_Free(Light *light)
{
    if (light) {
        UNLOAD(&light->Direction);
        free(light);
    }
}
