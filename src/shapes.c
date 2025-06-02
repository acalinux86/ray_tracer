#include "shapes.h"

const char *object_kinds[COUNT_OBJECT_KINDS] = {
    [OBJECT_SPHERE] = "SPHERE",
};

bool compare_colors(Color a, Color b)
{
    return (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}

void free_objects(Objects *objs)
{
    if (objs) {
        free(objs->items);
        objs->items = NULL;
        objs->count = objs->capacity = 0;
    }
}

void insert_object(Objects *objs, Object *obj)
{
    if (objs->count >= objs->capacity) {
        objs->capacity = objs->capacity == 0 ? INITIAL_CAPACITY : objs->capacity * 2;
        objs->items = realloc(objs->items, sizeof(Object)*objs->capacity);
        if (objs->items == NULL) {
            Log_Out(ERROR, "Failed To Reallocate Items.\n");
            return;
        }
    }

    objs->items[objs->count++] = deep_copy_object(obj);
}

unsigned int search_object(Objects *objs, const Object *target)
{
    assert(objs && target);
    if (objs->count == 0) return UINT_MAX;
    for (unsigned int i = 0; i < objs->count; ++i) {
        if (objs->items[i].kind != target->kind) continue;

        switch(target->kind) {
        case OBJECT_SPHERE:
            const Sphere *current = objs->items[i].object.sphere;
            const Sphere *target_sphere = target->object.sphere;
            if (current->radius == target_sphere->radius &&
            TEST_MATRIX(current->position, target_sphere->position) &&
            compare_colors(current->color, target_sphere->color)) {
                return i;
            }

            break;

        default:
            Log_Out(ERROR, "Unknown Object Type: %s.\n", object_kinds[target->kind]);
            return UINT_MAX;
        }
    }

    Log_Out(ERROR, "Target Not Found In Array.\n");
    return UINT_MAX;
}

bool delete_object(Objects *objs, unsigned int index)
{
    if (objs  == NULL) return false;
    if (index >= objs->count) return false;

    Object *target = &objs->items[index];

    switch(target->kind) {
    case OBJECT_SPHERE:
        free_sphere(target->object.sphere);
        break;

    default:
        Log_Out(ERROR, "Unknown Object Type: %s.\n", object_kinds[target->kind]);
        return false;
    }

    // Shift Elements
    memmove(target, &objs->items[index + 1], sizeof(Object) * objs->count - index - 1);
    return false;
}

void pop_object(Objects *objs)
{
    if (objs->count > 0) {
        delete_object(objs, objs->count - 1); // pop last element
    }
}

Object deep_copy_object(const Object *source)
{
    Object destination;
    destination.kind = source->kind;

    switch (source->kind) {
    case OBJECT_SPHERE:
        destination.object.sphere = malloc(sizeof(Sphere));
        if (destination.object.sphere == NULL) {
            Log_Out(ERROR, "Failed to Allocate Memory For Sphere.\n");
            exit(EXIT_FAILURE);
        }
        *destination.object.sphere = *source->object.sphere;
        break;

    default:
        Log_Out(ERROR, "Unknown Object Type: %s.\n", object_kinds[source->kind]);
        exit(EXIT_FAILURE);
    }

    return destination;
}

Sphere *new_sphere(Vector3 position, float radius, Color color)
{
    Sphere *sphere = (Sphere *) malloc(sizeof(Sphere));
    if (sphere == NULL) {
        Log_Out(ERROR, "%s.\n", "Failed to Allocate Memory For Sphere");
        return NULL;
    }

    sphere->color = color;
    sphere->position = position;
    sphere->radius = radius;
    return sphere;
}

Object sphere_to_object(Sphere *sphere)
{
    Object object;
    object.object.sphere = sphere;
    object.kind = OBJECT_SPHERE;

    return object;
}

void free_sphere(Sphere *sphere)
{
    if (sphere) {
        UNLOAD(&sphere->position);
        free(sphere);
    }
}

Vector3 ComputeSurfaceNormal(Sphere *sphere, Vector3 intersectionPoint)
{
    Vector3 Surface_Normal = Vector3_Subtract(&intersectionPoint, &sphere->position);
    Vector3 Noramalize_Surface_Normal =  Vector3_Normalize(&Surface_Normal);

    UNLOAD(&Surface_Normal);
    return Noramalize_Surface_Normal;
}
