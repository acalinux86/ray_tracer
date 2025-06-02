#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "scene.h"
#include "camera.h"
#include "shapes.h"
#include "ray.h"
#include "light.h"

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "fasic.h"

// Image Width and Height
#define WIDTH 1920
#define HEIGHT 1080

#define SAMPLES 2  // Number of samples per pixel

// Pixel Structure and Information (RGBA)
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Pixel;

// Allocates Memory for each pixel totaling (WIDTH*HEIGHT) pixels
Pixel *pixels_alloc();
// Free Memory Allocated for the pixels
void pixels_dealloc(Pixel *pixels);
// Writes to the pixels array, each pixel of the sphere that has intersected the ray
void RenderSphere(Sphere *sphere, Pixel *pixels);
#endif // RENDER_H
