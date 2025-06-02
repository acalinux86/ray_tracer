#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"
#define FASIC_IMPLEMENTATION
#include "fasic.h"

typedef struct {
    Vector3 Position;
    Vector3 LookAt;
    float Fov;
} Camera;

Camera *Camera_Create(Vector3 position, Vector3 look_at, float fov);
void Camera_Free(Camera *camera);
Vector3 GetCameraDirection(const Camera *camera);

#endif /*CAMERA_H*/
