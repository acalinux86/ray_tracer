#include "./camera.h"

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

Vector3 get_fov(Vector3 viewport)
{
    float distance = GET_ELEMENT(viewport, 2, 0);
    float h = 2 * atan2(GET_ELEMENT(viewport, 0, 0)/2, distance);
    float v = 2 * atan2(GET_ELEMENT(viewport, 1, 0)/2, distance);

    return Create_Vector3(h, v, distance);
}

void camera_prop(const Camera *camera)
{
    Log_Out(INFO, "Camera Properties:\n");
    float x = GET_ELEMENT(camera->Position, 0 , 0);
    float y = GET_ELEMENT(camera->Position, 1 , 0);
    float z = GET_ELEMENT(camera->Position, 2 , 0);
    Log_Out(INFO, "    Camera Position:                 (%f, %f, %f).\n", x , y , z);

    float a = GET_ELEMENT(camera->fov, 0 , 0);
    float b = GET_ELEMENT(camera->fov, 1 , 0);
    Log_Out(INFO, "    Camera Field of View in Degrees: (Horizontal: %f, Vertical: %f).\n", a , b);
    Log_Out(INFO, "\n");
}
