#include "camera.h"

Camera *Camera_Create(Vector3 position, Vector3 look_at, float fov)
{
    Camera *camera = (Camera *)malloc(sizeof(Camera));
    if (camera == NULL) {
        Log_Out(ERROR, "%s.\n", "Failed To Allocate Memory For Camera");
        return NULL;
    }

    camera->Fov = fov;
    camera->LookAt = look_at;
    camera->Position = position;
    return camera;
}

void Camera_Free(Camera *camera)
{
    if (camera) {
        UNLOAD(&camera->Position);
        UNLOAD(&camera->LookAt);
        free(camera);
    }
}

Vector3 GetCameraDirection(const Camera *camera)
{
    if (!camera) return Create_Vector3(0 , 0 , 0);

    Vector3 LookAt   = camera->LookAt;
    Vector3 Position = camera->Position;

    Vector3 Direction = Vector3_Subtract(&LookAt , &Position);
    Vector3 Normalized_Direction = Vector3_Normalize(&Direction);

    UNLOAD(&LookAt);
    UNLOAD(&Position);
    UNLOAD(&Direction);

    return Normalized_Direction;
}
