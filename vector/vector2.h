#ifndef VECTOR2_IMPLEMENTATION
#define VECTOR2_IMPLEMENTATION

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "./fasic.h"

typedef Fasic_Matrix Vector2;

// Function that creates a vector from three given values
Vector2 Create_Vector2(float x, float y);

// Function that Adds Two Vector
Vector2 Vector2_Add(Vector2 *A, Vector2 *B);

// Function that Subtracts Two Vector
Vector2 Vector2_Subtract(Vector2 *A, Vector2 *B);

// Function that returns the Dot Product of two Vectors -> (a float)
float Vector2_Dot(Vector2 *A, Vector2 *B);

// Float and Vector Dot Product
Vector2 float_vector2_dot(Vector2 *A, float B);

// Function that Normalizes a Vector
Vector2 Vector2_Normalize(Vector2 *A);

// Function that Prints a Vector
void PRINT_VECTOR2(Vector2 vec, const char *name);

#define PRINT_VEC2(vec) PRINT_VECTOR2(vec, #vec)

#endif /*VECTOR2_IMPLEMENTATION*/
