#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

#include "./shapes.h"
#include "./scene.h"
#include "./camera.h"
#include "./render.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"

#define Z 10.0f

#define WHITE ((Color){255, 255, 255, 255})
#define GREEN ((Color){0,   255, 0,   255})
#define RED   ((Color){255, 0,   0,   255})
#define BLUE  ((Color){0,   0,   255, 255})
#define BLACK ((Color){0,   0,   0 ,  255 })

// Image Width and Height
#define WIDTH  1980
#define HEIGHT 1080

int main()
{
    Log_Out(INFO, "Hello, World From Ray Tracer.\n");

    Objects objects = {0};
    Sphere *sphere_white = new_sphere(Create_Vector3(0.0f, -1.0f, 10.0f), 1.0f, WHITE);
    Sphere *sphere_green = new_sphere(Create_Vector3(2.0f, 0.0f, 40.0f), 1.0f, GREEN);
    Sphere *sphere_red   = new_sphere(Create_Vector3(-2.0f, 0.0f, 20.0f), 1.0f, RED);
    Sphere *sphere_blue  = new_sphere(Create_Vector3(0.0f, 1.0f, 15.0f), 1.0f, BLUE);

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
    Vector3 viewport = Create_Vector3(10, 10, Z);

    // Camera
    Camera *camera = new_camera(Create_Vector3(0, 0, -10), get_fov(viewport, Z));
    assert(camera != NULL);

    // Pixel Array
    Pixel *pixels = pixels_alloc(WIDTH, HEIGHT);
    assert(pixels != NULL);

    // Scene
    Scene scene = {0};
    scene.objects = &objects;

    // Render Scene
    render_scene(&scene, camera, pixels, HEIGHT, WIDTH, Z, viewport, BLACK);

    const char *image_path = "images/sphere.png";
    if (!stbi_write_png(image_path, WIDTH, HEIGHT, 4, pixels, sizeof(Pixel)*WIDTH)) {
        Log_Out(ERROR, "Failed to Save Image: %s.\n", image_path);
        return 1;
    }

    // Free Resources
    free_camera(camera);
    pixels_dealloc(pixels);
    free_sphere(sphere_white);
    free_sphere(sphere_green);
    free_sphere(sphere_red);
    free_sphere(sphere_blue);
    free(objects.items);
    return 0;
}
