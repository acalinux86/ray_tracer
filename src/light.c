#include "./light.h"

const char *light_kind_as_cstr[] = {
    [LIGHT_POINT] = "LIGHT_POINT",
    [LIGHT_DIRECTIONAL] = "LIGHT_DIRECTIONAL",
    [LIGHT_AMBIENT] = "LIGHT_AMBIENT",
};

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
    Color color = {
        (uint8_t)fmin(255, c.r * intensity),
        (uint8_t)fmin(255, c.g * intensity),
        (uint8_t)fmin(255, c.b * intensity),
        255,
    };

//    print_color(color);
    return color;
}

void light_prop(Light *light)
{
    Log_Out(INFO, "Light Properties: \n");
    float x = GET_ELEMENT(light->Direction, 0 , 0);
    float y = GET_ELEMENT(light->Direction, 1 , 0);
    float z = GET_ELEMENT(light->Direction, 2 , 0);
    Log_Out(INFO, "    Light Direction: %f, %f, %f.\n", x , y , z);
    Log_Out(INFO, "    Light Kind:      %s\n", light_kind_as_cstr[light->kind]);
    Log_Out(INFO, "    Light Intensity: %f.\n", light->intensity);
    Log_Out(INFO, "\n");
}
