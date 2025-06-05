#include "./scene.h"
#include <float.h>

Vector3 canvas_to_viewport(Vector3 viewport, int x, int y, int height, int width, int distance)
{
    float aspect_ratio = (float)width / height;
    return Create_Vector3(
    x * (GET_ELEMENT(viewport, 0, 0) / width * aspect_ratio),
    y * (GET_ELEMENT(viewport, 1, 0) / height),
        distance
    );
}

float compute_lighting(Scene *scene, Vector3 *P, Vector3 *N) {
    float intensity = 0.1;

    Vector3 light_dir = Vector3_Normalize(&scene->light->Direction);
    Vector3 normal = Vector3_Normalize(N);

    // Diffuse lighting
    float diffuse = Vector3_Dot(&normal, &light_dir);
    if (diffuse > 0) {
        intensity += scene->light->intensity * diffuse;
    }

    UNLOAD(&light_dir);
    UNLOAD(&normal);
    return fmin(intensity, 1.0f); // Clamp to [0,1]
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

    UNLOAD(&ray_close);
    UNLOAD(&N);
    UNLOAD(&P);
    UNLOAD(&N_norm);

    return color;
}

void render_scene(Scene *scene, Camera *camera, Pixel *pixels, int height, int width, int distance, Vector3 viewport)
{
    if (width <= 0 || height <= 0) return;
    for (int i = -width/2; i < width/2; ++i) {
        for (int j = -height/2; j < height/2; ++j) {
            Vector3 view = canvas_to_viewport(viewport, i , j , width, height, distance);
            Vector3 origin = Create_Vector3(GET_ELEMENT(camera->Position, 0 , 0), GET_ELEMENT(camera->Position, 1 , 0), GET_ELEMENT(camera->Position, 2 , 0));
            Ray *ray = new_ray(origin, view);
            Color color = trace_ray(scene, ray, 1, FLT_MAX);
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
