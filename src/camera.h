#ifndef CAMERA_H
#define CAMERA_H

#include "./vector3.h"
#include "./vector2.h"
#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

typedef struct {
    Vector3 Position;
    Vector2 fov;
} Camera;

Camera *new_camera(Vector3 position, Vector2 fov);
void free_camera(Camera *camera);
Vector2 get_fov(Vector2 viewport, float distance);

#endif /*CAMERA_H*/
