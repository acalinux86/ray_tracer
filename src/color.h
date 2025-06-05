#ifndef COLOR_H_
#define COLOR_H_

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

void print_color(Color color);

#endif // COLOR_H_
