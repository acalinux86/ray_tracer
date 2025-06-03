#ifndef VECTOR3_IMPLEMENTATION
#define VECTOR3_IMPLEMENTATION

#define FASIC_IMPLEMENTATION
#define UPPERCASE_
#include "fasic.h"

typedef Fasic_Matrix Vector3;

// Function that creates a vector from three given values
Vector3 Create_Vector3(float x, float y, float z);

// Function that Adds Two Vector
Vector3 Vector3_Add(Vector3 *A, Vector3 *B);

// Function that Subtracts Two Vector
Vector3 Vector3_Subtract(Vector3 *A, Vector3 *B);

// Function that returns the Dot Product of two Vectors -> (a float)
float Vector3_Dot(Vector3 *A, Vector3 *B);

// Function that Returns A Cross Product of two Vectors
Vector3 Vector3_Cross(Vector3 *A, Vector3 *B);

// Float and Vector Dot Product
Vector3 float_vector3_dot(Vector3 *A, float B);

// Scaling a Vector
Vector3 Vector3_Scaling(Vector3 A, float b);

// Function that Normalizes a Vector
Vector3 Vector3_Normalize(Vector3 *A);

// Length of a vector
float Vector3_Length(Vector3 *A);

// Function that Prints a Vector
void PRINT_VECTOR3(Vector3 vec, const char *name);
#define PRINT_VEC3(vec) PRINT_VECTOR3(vec, #vec)

#endif /*VECTOR3_IMPLEMENTATION*/
