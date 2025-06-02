#include "camera.h"

Camera *new_camera(Vector3 position, Vector2 fov)
{
    Camera *camera = (Camera *)malloc(sizeof(Camera));
    if (camera == NULL) {
        Log_Out(ERROR, "%s.\n", "Failed To Allocate Memory For Camera");
        return NULL;
    }

    camera->fov = fov;
    camera->Position = position;
    return camera;
}

void free_camera(Camera *camera)
{
    if (camera) {
        UNLOAD(&camera->Position);
        UNLOAD(&camera->fov);
        free(camera);
    }
}

Vector2 get_fov(Vector3 viewport, float distance)
{
    float h = 2 * atan2(GET_ELEMENT(viewport, 0, 0)/2, distance);
    float v = 2 * atan2(GET_ELEMENT(viewport, 1, 0)/2, distance);

    return Create_Vector2(h, v);
}
