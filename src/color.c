#include "./color.h"

void print_color(Color color)
{
    Log_Out(INFO, "Color:\n");
    printf("        R: %u\n", color.r);
    printf("        G: %u\n", color.g);
    printf("        B: %u\n", color.b);
    printf("        A: %u\n", color.a);
}
