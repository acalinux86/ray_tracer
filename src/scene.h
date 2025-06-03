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
#include "./light.h"

typedef struct Scene {
    Objects *objects;
    Color background;
    Light *light;
    int samples; // Samples per pixel
} Scene;

Vector3 canvas_to_viewport(Vector3 viewport, int x, int y, int height, int width, int distance);
float compute_lighting(Scene *scene, Vector3 *P, Vector3 *N);
Color trace_ray(Scene *scene, Ray *ray, float t_min, float t_max);
Color sample_pixel(Scene *scene, Camera *camera, float x, float y, int width, int height, int distance, Vector3 viewport);
void render_scene(Scene *scene, Camera *camera, Pixel *pixels, int height, int width, int distance, Vector3 viewport);

#endif /*SCENE_H*/
