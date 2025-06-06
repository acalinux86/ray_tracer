#include "./ffmpeg.h"

bool build_animation(const char *images_path, const char *output_path, int framerate)
{
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", framerate);
    const char *build_ffmpeg[] = {
        "ffmpeg", "-framerate", buffer,
        "-i", images_path"/frame_%d.png",
        "-c:v", "libx264",
        "-pix_fmt", "yuv420p",
        "-vf", "setpts=5*PTS",
        output_path, NULL
    };

    Fasic_Cmd Cmd = {0};
    append_to_array_many(&Cmd, build_ffmpeg);
    if (!build_cmd(&Cmd)) return false;
    cmd.count = 0;

    Log_Out(INFO, "Successfully Saved Output Video to %s.\n", output_path);
    free(&cmd.items);
    return true;
}
