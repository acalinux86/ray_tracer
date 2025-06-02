#include "render.h"

// Allocates Memory for each pixel totaling (WIDTH*HEIGHT) pixels
Pixel *pixels_alloc() {
    Pixel *pixels = (Pixel *) malloc(sizeof(Pixel) * WIDTH*HEIGHT);
    if (pixels == NULL) {
        Log_Out(ERROR, "Failed To Allocate Memory For Pixels.");
        return NULL;
    }
    return pixels;
}

// Free Memory Allocated for the pixels
void pixels_dealloc(Pixel *pixels) {
    if(pixels) {
        free(pixels);
        pixels = NULL;
    }
}

// Writes to the pixels array, each pixel of the sphere that has intersected the ray
void RenderSphere(Sphere *sphere, Pixel *pixels) {
    float aspect_ratio = (float) WIDTH / (float) HEIGHT;

    float r = sphere->color.r;
    float g = sphere->color.g;
    float b = sphere->color.b;
    float a = sphere->color.a;

    // Camera camera = { Create_Vector3(0 , 0 , 500) };

    Vector3 lightDir = Create_Vector3(1.0f, 1.0f, 1.0f);
    Light *light = Light_New(lightDir);

    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            float total_r = 0.0f , total_g = 0.0f , total_b = 0.0f, total_a = 0.0f;

            // Supersampling loop
            for (int k = 0; k < SAMPLES; ++k) {
                float u = (float) (i + (k % 2) * 0.5f) / WIDTH;
                float v = (float) (j + (k / 2) * 0.5f) / HEIGHT;
                // Adjust for aspect ratio
                float x = (2.0f * u - 1.0f) * aspect_ratio;
                float y = 1.0f - 2.0f * v;

                Ray *ray = Ray_New(Create_Vector3(0 , 0 , 500), Create_Vector3(x, y, -1.0f));

                float t;
                int index = j * WIDTH + i;
                if (RaySphereIntersection(ray, sphere, &t)) {
                    Vector3 tDir = float_vector3_dot(&ray->Direction , t);
                    Vector3 intersectionPoint = Vector3_Add(&ray->Origin , &tDir);

                    Vector3 surfNormal = ComputeSurfaceNormal(sphere , intersectionPoint);

                    float diffuse = Vector3_Dot(&surfNormal , &light->Direction);
                    if (diffuse < 0.0f) diffuse = 0.0f;

                    float ambient = 0.1f;
                    float ambientIntensity = ambient + diffuse;
                    if(ambientIntensity > 1.0f) ambientIntensity = 1.0f;

                    total_r += r * ambientIntensity;
                    total_g += g * ambientIntensity;
                    total_b += b * ambientIntensity;
                    total_a += a * ambientIntensity;

                    // If there is an intersection, use the sphere's color
                    pixels[index].r = (uint8_t) ((total_r/ SAMPLES) * 255);
                    pixels[index].g = (uint8_t) ((total_g/ SAMPLES) * 255);
                    pixels[index].b = (uint8_t) ((total_b/ SAMPLES) * 255);
                    pixels[index].a = (uint8_t) ((total_a/ SAMPLES) * 255);; // Fully opaque

                    UNLOAD(&tDir);
                    UNLOAD(&intersectionPoint);
                    UNLOAD(&surfNormal);

                } else {
                    pixels[index].r = (uint8_t) (0 * 255);
                    pixels[index].g = (uint8_t) (0 * 255);
                    pixels[index].b = (uint8_t) (0 * 255);
                    pixels[index].a = 255; // Fully opaque
                }
                Ray_Free(ray);
            }
        }
    }
    Light_Free(light);
}
