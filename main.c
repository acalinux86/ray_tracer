#define FASIC_IMPLEMENTATION
#include "./thirdparty/fasic.h"

#define BUILD_DIR "build/"  // Build Directory
#define SRC_DIR   "src/"    // Source Directory
#define VEC_DIR   "vector/" // Vector Directory
#define OBJ_DIR   "obj/"    // Object Directory
#define LEX_DIR   "lexer/"  // Lexer Directory
#define IMG_DIR   "images/" // Images Directory

// C Compiler
const char *CC = "gcc";

int main(void)
{
    // Build Folder: Where the final executable is
    if (!remove_directory(BUILD_DIR))   return 1;
    if (!make_new_directory(BUILD_DIR)) return 1;

    // Object Folder: Directory for Object Files
    if (!remove_directory  (OBJ_DIR)) return 1;
    if (!make_new_directory(OBJ_DIR)) return 1;

    // Images Folder: Directory For storing images
    if (!make_new_directory(IMG_DIR)) return 1;

    Fasic_Cmd cmd = {0};

    // Build Individual C files into Object files

    // Build Vector2 library
    const char *build_vector2[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-c", VEC_DIR"vector2.c", "-o", OBJ_DIR"vector2.o", "-lm",NULL};
    append_to_array_many(&cmd, build_vector2);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Vector3 Library
    const char *build_vector3[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-c", VEC_DIR"vector3.c", "-o", OBJ_DIR"vector3.o", "-lm",NULL};
    append_to_array_many(&cmd, build_vector3);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Camera File
    const char *build_camera[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-I./vector/", "-c", SRC_DIR"camera.c", "-o", OBJ_DIR"camera.o", "-lm", NULL};
    append_to_array_many(&cmd, build_camera);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Light File
    const char *build_light[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-I./vector/", "-c", SRC_DIR"light.c", "-o", OBJ_DIR"light.o", "-lm" ,NULL};
    append_to_array_many(&cmd, build_light);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Ray File
    const char *build_ray[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-I./vector/", "-c", SRC_DIR"ray.c", "-o", OBJ_DIR"ray.o", "-lm",NULL};
    append_to_array_many(&cmd, build_ray);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Render File
    const char *build_render[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-I./vector/", "-c", SRC_DIR"render.c", "-o", OBJ_DIR"render.o", "-lm",NULL};
    append_to_array_many(&cmd, build_render);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Color File
    const char *build_color[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-I./vector/", "-c", SRC_DIR"color.c", "-o", OBJ_DIR"color.o", "-lm",NULL};
    append_to_array_many(&cmd, build_color);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Scene File
    const char *build_scene[] = {CC, "-Wall", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-I./vector/", "-c", SRC_DIR"scene.c", "-o", OBJ_DIR"scene.o","-lm" ,NULL};
    append_to_array_many(&cmd, build_scene);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Shapes File
    const char *build_shapes[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-I./vector/", "-c", SRC_DIR"shapes.c", "-o", OBJ_DIR"shapes.o", "-lm",NULL};
    append_to_array_many(&cmd, build_shapes);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Lexer File
    const char *build_lexer[] = {CC, "-Wall", "-Werror", "-Wextra", "-ggdb", "-std=c17", "-D_DEFAULT_SOURCE", "-I./thirdparty/", "-c", LEX_DIR"lexer.c", "-o", OBJ_DIR"lexer.o", "-lm",NULL};
    append_to_array_many(&cmd, build_lexer);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    // Build Main Ray Tracer Program
    const char *build_ray_tracer[] = {CC, "-Wall", "-Ofast", "-ggdb", "-I./thirdparty/", "-I./vector/", "-I./lexer/", "-I./stb/",OBJ_DIR"vector2.o", OBJ_DIR"vector3.o", OBJ_DIR"camera.o", OBJ_DIR"light.o", OBJ_DIR"ray.o", OBJ_DIR"render.o", OBJ_DIR"color.o", OBJ_DIR"shapes.o", OBJ_DIR"scene.o", OBJ_DIR"lexer.o", SRC_DIR"ray_tracer.c", "-o", BUILD_DIR"ray_tracer", "-lm",NULL};
    append_to_array_many(&cmd, build_ray_tracer);
    if (!build_cmd(&cmd)) return 1;
    cmd.count = 0;

    return 0;
}
