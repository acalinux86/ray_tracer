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

Color trace_ray(Scene *scene, Ray *ray, float t_min, float t_max, Color background)
{
    float closest_t = t_max;
    Sphere *sphere = NULL;
    for (int i = 0; i < (int)scene->objects->count; ++i) {
        float t1, t2;
        if (scene->objects->items[i].kind == OBJECT_SPHERE) {
            if (RaySphereIntersection(ray, scene->objects->items[i].object.sphere, &t1, &t2)) {
                if (t1 > t_min && t1 < closest_t) {
                    closest_t = t1;
                    sphere = scene->objects->items[i].object.sphere;
                }
                if (t2 > t_min && t2 < closest_t) {
                    closest_t = t2;
                    sphere = scene->objects->items[i].object.sphere;
                }
            }
        }
    }
    return sphere ? sphere->color : background;
}

void render_scene(Scene *scene, Camera *camera, Pixel *pixels, int height, int width, int distance, Vector3 viewport, Color background)
{
    if (width <= 0 || height <= 0) return;
    for (int i = -width/2; i < width/2; ++i) {
        for (int j = -height/2; j < height/2; ++j) {
            Vector3 view = canvas_to_viewport(viewport, i , j , width, height, distance);
            Vector3 origin = Create_Vector3(GET_ELEMENT(camera->Position, 0 , 0), GET_ELEMENT(camera->Position, 1 , 0), GET_ELEMENT(camera->Position, 2 , 0));
            Ray *ray = new_ray(origin, view);
            Color color = trace_ray(scene, ray, 1, FLT_MAX, background);
            int x = i + width / 2;
            int y = j + height / 2;
            if (x >= 0 && x < width && y >= 0 && y < height) {
                int index = y * width + x;
                put_pixel(pixels, index, color);
            }
            free_ray(ray);
        }
    }
}
