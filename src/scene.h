#ifndef SCENE_H
#define SCENE_H

#include "vector3.h"
#include "shapes.h"
#include "camera.h"

typedef struct Scene {
    Objects *objects;
    Camera Cam;
    Color Background;
} Scene;

#endif /*SCENE_H*/
