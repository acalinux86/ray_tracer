#include "./ffmpeg.h"

bool build_animation(const char *images_dir, const char *output_path, int framerate)
{
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", framerate);

    char images_path[20];
    snprintf(images_path, sizeof(images_path), "%s/frame_%%d.png", images_dir);

    const char *build_ffmpeg[] = {
        "ffmpeg",
        "-framerate", buffer,
        "-i", images_path,
        "-c:v", "libx264",
        "-pix_fmt", "yuv420p",
        "-vf", "setpts=5*PTS",
        output_path, NULL
    };

    Fasic_Cmd Cmd = {0};
    append_to_array_many(&Cmd, build_ffmpeg);
    if (!build_cmd(&Cmd)) return false;
    Cmd.count = 0;

    Log_Out(INFO, "Successfully Saved Output Video to %s.\n", output_path);
    free(Cmd.items);
    return true;
}
