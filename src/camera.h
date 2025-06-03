#ifndef CAMERA_H
#define CAMERA_H

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

#include "./vector3.h"
#include "./vector2.h"

#define PI 3.14159

typedef struct {
    Vector3 Position;
    Vector2 fov;
} Camera;

Camera *new_camera(Vector3 position, Vector2 fov);
void free_camera(Camera *camera);
Vector2 get_fov(Vector2 viewport, float distance);
void camera_prop(const Camera *camera); // Prints Out camera properties
#endif /*CAMERA_H*/
