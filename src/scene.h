#ifndef SCENE_H
#define SCENE_H

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

#include "./vector3.h"
#include "./shapes.h"
#include "./camera.h"
#include "./render.h"
#include "./ray.h"

typedef struct Scene {
    Objects *objects;
} Scene;

Vector3 canvas_to_viewport(Vector3 viewport, int x, int y, int height, int width, int distance);
Color trace_ray(Scene *scene, Ray *ray, float t_min, float t_max, Color background);
void render_scene(Scene *scene, Camera *camera, Pixel *pixels, int height, int width, int distance, Vector3 viewport, Color background);

#endif /*SCENE_H*/
