#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

#include "./shapes.h"
#include "./scene.h"
#include "./camera.h"
#include "./render.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"

#define FPS 30
#define MAX_BUFFER_LEN 20

#define Z 3.0f

#define WHITE   ((Color){255, 255, 255, 255})
#define GREEN   ((Color){0,   255, 0,   255})
#define RED     ((Color){255, 0,   0,   255})
#define BLUE    ((Color){0,   0,   255, 255})
#define BLACK   ((Color){0,   0,   0 ,  255})

#define YELLOW  ((Color){255, 255, 0,   255})
#define U  ((Color){0, 255, 255,   255})

// Viewport
#define viewport (Create_Vector3(6.0f, 6.0f, Z))

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
    Sphere *sphere_white = new_sphere(Create_Vector3(-4.0f , 0.0f, 5.0f), 0.5f,  WHITE);
    Sphere *sphere_white1 = new_sphere(Create_Vector3(-3.0f , 0.0f, 5.0f), 0.5f,  WHITE);
    Sphere *sphere_white2 = new_sphere(Create_Vector3(-2.0f , 0.0f, 5.0f), 0.5f,  WHITE);
    Sphere *sphere_white3 = new_sphere(Create_Vector3(-1.0f , 0.0f, 5.0f), 0.5f,  WHITE);
    Sphere *sphere_white4 = new_sphere(Create_Vector3(0.0f , 0.0f, 5.0f), 0.5f,  WHITE);
    Sphere *sphere_white5 = new_sphere(Create_Vector3(1.0f , 0.0f, 5.0f), 0.5f,  WHITE);
    Sphere *sphere_white6 = new_sphere(Create_Vector3(2.0f , 0.0f, 5.0f), 0.5f,  WHITE);
    Sphere *sphere_white7 = new_sphere(Create_Vector3(3.0f , 0.0f, 5.0f), 0.5f,  WHITE);
    Sphere *sphere_white8 = new_sphere(Create_Vector3(4.0f , 0.0f, 5.0f), 0.5f,  WHITE);

    // Create temporary objects on stack
    Object obj_white = sphere_to_object(sphere_white);
    Object obj_white1 = sphere_to_object(sphere_white1);
    Object obj_white2   = sphere_to_object(sphere_white2);
    Object obj_white3  = sphere_to_object(sphere_white3);
    Object obj_white4  = sphere_to_object(sphere_white4);
    Object obj_white5  = sphere_to_object(sphere_white5);
    Object obj_white6  = sphere_to_object(sphere_white6);
    Object obj_white7  = sphere_to_object(sphere_white7);
    Object obj_white8  = sphere_to_object(sphere_white8);

    insert_object(&objects, &obj_white);
    insert_object(&objects, &obj_white1);
    insert_object(&objects, &obj_white2);
    insert_object(&objects, &obj_white3);
    insert_object(&objects, &obj_white4);
    insert_object(&objects, &obj_white5);
    insert_object(&objects, &obj_white6);
    insert_object(&objects, &obj_white7);
    insert_object(&objects, &obj_white8);

    for (int i = 0; i < FPS; ++i) {
        // Camera
        Camera *camera = new_camera(Create_Vector3(i*0.1, i*0.2, i*(-0.3)), get_fov(viewport));
        assert(camera != NULL);
        camera_prop(camera);

        // Pixel Array
        Pixel *pixels = pixels_alloc(WIDTH, HEIGHT);
        assert(pixels != NULL);

        // Light
        Vector3 dir = Create_Vector3((float) 1.0f*i, 2.0f*i, 3.0f*i);
        Vector3 dir_norm = Vector3_Normalize(&dir);
        Light *light = new_light(dir_norm, LIGHT_DIRECTIONAL, 1.0f*i);
        assert(light != NULL);
        light_prop(light);

        // Scene
        Scene scene = {0};
        scene.objects = &objects;
        scene.background = BLACK;
        scene.light = light;
        scene.samples = SAMPLES;

        // Render Scene
        render_scene(&scene, camera, pixels, HEIGHT, WIDTH, Z, viewport);

        char buffer[MAX_BUFFER_LEN];
        snprintf(buffer, sizeof(buffer), "images/frame_%0i.png", i);
        const char *image_path = buffer;
        if (!stbi_write_png(image_path, WIDTH, HEIGHT, 4, pixels, sizeof(Pixel)*WIDTH)) {
            Log_Out(ERROR, "Failed to Save Image: %s.\n", image_path);
            return 1;
        }

        Log_Out(INFO, "Successfully Saved Image to %s.\n", image_path);

        free_camera(camera);
        free_light(scene.light);
        pixels_dealloc(pixels);
        UNLOAD(&dir);
    }

    // Free Resources
    free_sphere(sphere_white);
    free(objects.items);
//    UNLOAD(&viewport);
    return 0;
}
