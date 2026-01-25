#include "init.h"

#include "raylib.h"

#include "../text/text.h"
#include "../plot/plot_math.h"
#include "../files/open_files.h"

int init(const Options options) {
    ConfigFlags flags = 0;
    if (options.enable_vsync) flags |= FLAG_VSYNC_HINT;
    if (options.enable_msaa)  flags |= FLAG_MSAA_4X_HINT;
    SetConfigFlags(flags);

    InitWindow(PLOT_WIDTH, PLOT_HEIGHT, "Spęczanie");
    SetExitKey(KEY_NULL);
    font_init();

    return 0;
}

void standard_exit() {
    font_unload();
    CloseWindow();
    clear_files();
}
