#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

typedef struct {
    int auto_import_x;
    int auto_import_y;
    bool auto_import;
} Options;

int process_args(int argc, char** argv, Options* options_out);

#endif //ARGS_H
