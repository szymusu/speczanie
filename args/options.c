#include "options.h"

Options options_default() {
    return (Options) {
        .auto_import_x = -1,
        .auto_import_y = -1,
        .auto_import = false,
        .show_fps = false,
        .enable_vsync = false,
        .enable_msaa = false,
    };
}
