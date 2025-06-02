#include "./vector2.h"

// Function that creates a vector from three given values
Vector2 Create_Vector2(float x, float y) {
    Vector2 vec = CREATE_MATRIX(2, 1);
    float values[2] = {x, y};
    for (size_t i = 0; i < 2; i++) {
        SET_ELEMENT(vec, i, 0, values[i]);
    }
    return vec;
}

// Function that Adds Two Vector
Vector2 Vector2_Add(Vector2 *A, Vector2 *B) {
    return MATRIX_ADD(A, B);
}

// Function that Subtracts Two Vector
Vector2 Vector2_Subtract(Vector2 *A, Vector2 *B) {
    return MATRIX_SUBTRACT(A, B);
}

// Function that returns the Dot Product of two Vectors -> (a float)
float Vector2_Dot(Vector2 *A, Vector2 *B) {
    Vector2 result = HADAMARD_PRODUCT(A, B);
    float product = 0;
    for (size_t i = 0; i < result.nrows; ++i) {
        for (size_t j = 0; j < result.ncols; ++j) {
            product += GET_ELEMENT(result, i , j);
        }
    }
    UNLOAD(&result); // Free the temporary matrix
    return product;
}

// Float and Vector Dot Product
Vector2 float_vector2_dot(Vector2 *A, float B) {
    float x , y;
    x = GET_ELEMENT(*A, 0 , 0);
    y = GET_ELEMENT(*A, 1 , 0);

    return Create_Vector2(B*x , B*y);
}

// Function that Normalizes a Vector
Vector2 Vector2_Normalize(Vector2 *A) {
    float x , y;
    x = GET_ELEMENT(*A, 0, 0);
    y = GET_ELEMENT(*A, 1, 0);

    float Magnitude = sqrt(((x*x)+(y*y)));
    if (Magnitude == 0) {
        return Create_Vector2(0 , 0);
    }

    return Create_Vector2(x/Magnitude, y/Magnitude);
}

// Function that Prints a Vector
void PRINT_VECTOR2(Vector2 vec, const char *name) {
    print_matrix(vec, name);
}
