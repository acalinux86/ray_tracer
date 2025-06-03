#include "./vector3.h"

// Function that creates a vector from three given values
Vector3 Create_Vector3(float x, float y, float z) {
    Vector3 vec = CREATE_MATRIX(3, 1);
    float values[3] = {x, y, z};
    for (size_t i = 0; i < 3; i++) {
        SET_ELEMENT(vec, i, 0, values[i]);
    }
    return vec;
}

// Function that Adds Two Vector
Vector3 Vector3_Add(Vector3 *A, Vector3 *B) {
    return MATRIX_ADD(A, B);
}

// Function that Subtracts Two Vector
Vector3 Vector3_Subtract(Vector3 *A, Vector3 *B) {
    return MATRIX_SUBTRACT(A, B);
}

// Function that returns the Dot Product of two Vectors -> (a float)
float Vector3_Dot(Vector3 *A, Vector3 *B) {
    Vector3 result = HADAMARD_PRODUCT(A, B);
    float product = 0;
    for (size_t i = 0; i < result.nrows; ++i) {
        for (size_t j = 0; j < result.ncols; ++j) {
            product += GET_ELEMENT(result, i , j);
        }
    }
    UNLOAD(&result); // Free the temporary matrix
    return product;
}

// Function that Returns A Cross Product of two Vectors
Vector3 Vector3_Cross(Vector3 *A, Vector3 *B) {
    float a_x, a_y, a_z;
    float b_x, b_y, b_z;

    a_x = GET_ELEMENT(*A, 0, 0);
    a_y = GET_ELEMENT(*A, 1, 0);
    a_z = GET_ELEMENT(*A, 2, 0);
    b_x = GET_ELEMENT(*B, 0, 0);
    b_y = GET_ELEMENT(*B, 1, 0);
    b_z = GET_ELEMENT(*B, 2, 0);

    float cross_x = a_y * b_z - a_z * b_y;
    float cross_y = a_z * b_x - a_x * b_z;
    float cross_z = a_x * b_y - a_y * b_x;

    return Create_Vector3(cross_x, cross_y, cross_z);
}

// Float and Vector Dot Product
Vector3 float_vector3_dot(Vector3 *A, float B) {
    float x , y , z;
    x = GET_ELEMENT(*A, 0 , 0);
    y = GET_ELEMENT(*A, 1 , 0);
    z = GET_ELEMENT(*A, 2 , 0);

    return Create_Vector3(B*x , B*y , B*z);
}

// Length of a vector
float Magnitude(Vector3 *A)
{
    float x , y , z;
    x = GET_ELEMENT(*A, 0, 0);
    y = GET_ELEMENT(*A, 1, 0);
    z = GET_ELEMENT(*A, 2, 0);

    float Magnitude = sqrt(((x*x)+(y*y)+(z*z)));
    return Magnitude;
}

// Function that Normalizes a Vector
Vector3 Vector3_Normalize(Vector3 *A) {
    float x , y , z;
    x = GET_ELEMENT(*A, 0, 0);
    y = GET_ELEMENT(*A, 1, 0);
    z = GET_ELEMENT(*A, 2, 0);

    float Magnitude = sqrt(((x*x)+(y*y)+(z*z)));
    if (Magnitude == 0) {
        return Create_Vector3(0 , 0  , 0);
    }

    return Create_Vector3(x/Magnitude, y/Magnitude, z/Magnitude);
}

// Function that Prints a Vector
void PRINT_VECTOR3(Vector3 vec, const char *name) {
    print_matrix(vec, name);
}
