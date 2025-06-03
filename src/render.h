#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "camera.h"
#include "shapes.h"
#include "ray.h"
#include "light.h"

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "fasic.h"

// Pixel Structure and Information (RGBA)
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Pixel;

// Allocates Memory for each pixel totaling (WIDTH*HEIGHT) pixels
Pixel *pixels_alloc(int width, int height);
// Free Memory Allocated for the pixels
void pixels_dealloc(Pixel *pixels);
// Color a specific pixel
 void put_pixel(Pixel *pixels, int index, Color color);
// Writes to the pixels array, each pixel of the sphere that has intersected the ray
void RenderSphere(Sphere *sphere, Pixel *pixels, int width, int height, int samples);
#endif // RENDER_H
