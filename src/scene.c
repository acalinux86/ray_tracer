#include "scene.h"
#include <float.h>

Vector3 canvas_to_viewport(Vector3 viewport, int x, int y, int height, int width, int distance)
{
    if (width <= 0 || height <= 0) {
        return Create_Vector3(0, 0, distance);
    }
    float h = x * (GET_ELEMENT(viewport, 0, 0)/width);
    float v = y * (GET_ELEMENT(viewport, 1, 0)/height);

    return Create_Vector3(h, v, distance);
}

float compute_lighting(Scene *scene, Vector3 *P, Vector3 *N)
{
    float i = 0.0;
    float n_dot_l = Vector3_Dot(N, &scene->light->Direction);

    if (n_dot_l > 0) {
        i+= scene->light->intensity * n_dot_l;
    }

    return i;
}

Color trace_ray(Scene *scene, Ray *ray, float t_min, float t_max)
{
    float closest_t = t_max;
    Sphere *sphere = NULL;
    Vector3 P = {0};
    for (int i = 0; i < (int)scene->objects->count; ++i) {
        float t1, t2;
        if (scene->objects->items[i]->kind == OBJECT_SPHERE) {
            if (RaySphereIntersection(ray, scene->objects->items[i]->object.sphere, &t1, &t2)) {
                if (t1 > t_min && t1 < closest_t) {
                    closest_t = t1;
                    sphere = scene->objects->items[i]->object.sphere;
                }
                if (t2 > t_min && t2 < closest_t) {
                    closest_t = t2;
                    sphere = scene->objects->items[i]->object.sphere;

                }
            }
        }
    }
    if (!sphere) return scene->background;

    Vector3 ray_close = float_vector3_dot(&ray->Direction, closest_t);
    P = Vector3_Add(&ray->Origin, &ray_close);

    Vector3 N = Vector3_Subtract(&P, &sphere->position);
    Vector3 N_norm = Vector3_Normalize(&N);

    Color color = {0};
    if (sphere) color = color_intensity_mul(sphere->color, compute_lighting(scene, &P , &N_norm));

    // UNLOAD(&ray_close);
    // UNLOAD(&N);
    // UNLOAD(&N_norm);
    // UNLOAD(&P);
    // return sphere ? color : scene->background;

    // Debug: return distance as color
    float dist = Vector3_Length(&ray->Direction);
    uint8_t val = (uint8_t)fmin(255, dist*50);
    return (Color){val, val, val, 255};
}

Color sample_pixel(Scene *scene, Camera *camera, float x, float y, int width, int height, int distance, Vector3 viewport)
{
    Color accum = {0};
    for (int s = 0; s < scene->samples; s++) {
        // Jittered sampling within pixel
        float u = x + ((s % 2) + 0.5f) / 2.0f;
        float v = y + ((s / 2) + 0.5f) / 2.0f;

        Vector3 view = canvas_to_viewport(viewport, u, v, width, height, distance);
        Vector3 origin = Create_Vector3(GET_ELEMENT(camera->Position, 0 , 0), GET_ELEMENT(camera->Position, 1 , 0), GET_ELEMENT(camera->Position, 2 , 0));
        Ray *ray = new_ray(origin, view);
        Color sample = trace_ray(scene, ray, 1, FLT_MAX);
        free_ray(ray);

        accum.r += sample.r;
        accum.g += sample.g;
        accum.b += sample.b;
    }
    return (Color){
        accum.r / scene->samples,
        accum.g / scene->samples,
        accum.b / scene->samples,
        255
    };
}

void render_scene(Scene *scene, Camera *camera, Pixel *pixels, int height, int width, int distance, Vector3 viewport)
{
    if (width <= 0 || height <= 0) return;

    for (int py = 0; py < height; py++) {
        for (int px = 0; px < width; px++) {
            // Convert to [-1,1] range
            float x = (2.0f * (px + 0.5f) / width - 1.0f) * (width / (float)height);
            float y = (1.0f - 2.0f * (py + 0.5f) / height);
            Color color = sample_pixel(scene, camera, x, y, width, height, distance, viewport);
            put_pixel(pixels, py * width + px, color);
        }
    }
}
