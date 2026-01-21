#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

typedef struct {
    int auto_import_x;
    int auto_import_y;
    bool auto_import;

    bool show_fps;
} Options;

Options options_default();

#endif
