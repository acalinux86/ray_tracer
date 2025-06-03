#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

#include "./shapes.h"
#include "./scene.h"
#include "./camera.h"
#include "./render.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"

#define Z 1.0f

#define WHITE ((Color){255, 255, 255, 255})
#define GREEN ((Color){0,   255, 0,   255})
#define RED   ((Color){255, 0,   0,   255})
#define BLUE  ((Color){0,   0,   255, 255})
#define BLACK ((Color){0,   0,   0 ,  255})

int main(const int argc, const char **argv)
{
    if (argc != 4) {
        Log_Out(USAGE, "%s <WIDTH> <HEIGHT> <SAMPLES>.\n", argv[0]);
        return 1;
    }

    const int WIDTH   = atoi(argv[1]);
    const int HEIGHT  = atoi(argv[2]);
    const int SAMPLES = atoi(argv[3]);

    Log_Out(INFO, "Hello, World From Ray Tracer.\n");

    Objects objects = {0};
    Sphere *sphere_white = new_sphere(Create_Vector3(0.0f, 0.0f, 5.0f), 1.5f, WHITE);
    Sphere *sphere_green = new_sphere(Create_Vector3(2.0f, 0.0f, 7.0f), 1.0f, GREEN);
    Sphere *sphere_red   = new_sphere(Create_Vector3(-2.0f, 0.0f, 7.0f), 1.0f, RED);
    Sphere *sphere_blue  = new_sphere(Create_Vector3(0.0f, 2.0f, 6.0f), 1.0f, BLUE);

    // Create temporary objects on stack
    Object obj_white = sphere_to_object(sphere_white);
    Object obj_green = sphere_to_object(sphere_green);
    Object obj_red   = sphere_to_object(sphere_red);
    Object obj_blue  = sphere_to_object(sphere_blue);

    insert_object(&objects, &obj_white);
    insert_object(&objects, &obj_green);
    insert_object(&objects, &obj_red);
    insert_object(&objects, &obj_blue);

    // Viewport
    Vector3 viewport = Create_Vector3(8, 8, Z);

    // Camera
    Camera *camera = new_camera(Create_Vector3(0, 0, 2), get_fov(viewport, Z));
    assert(camera != NULL);
    camera_prop(camera);

    // Pixel Array
    Pixel *pixels = pixels_alloc(WIDTH, HEIGHT);
    assert(pixels != NULL);

    // Light
    Light *light = new_light(Create_Vector3(5, -5, 2), LIGHT_DIRECTIONAL, 0.5f);
    assert(light != NULL);

    // Scene
    Scene scene = {0};
    scene.objects = &objects;
    scene.background = BLACK;
    scene.light = light;
    scene.samples = SAMPLES;

    // Render Scene
    render_scene(&scene, camera, pixels, HEIGHT, WIDTH, Z, viewport);

    const char *image_path = "images/sphere.png";
    if (!stbi_write_png(image_path, WIDTH, HEIGHT, 4, pixels, sizeof(Pixel)*WIDTH)) {
        Log_Out(ERROR, "Failed to Save Image: %s.\n", image_path);
        return 1;
    }

    // Free Resources
    free_camera(camera);
    free_light(scene.light);
    pixels_dealloc(pixels);
    free_sphere(sphere_white);
    free_sphere(sphere_green);
    free_sphere(sphere_red);
    free_sphere(sphere_blue);
    free(objects.items);
    UNLOAD(&viewport);
    return 0;
}
