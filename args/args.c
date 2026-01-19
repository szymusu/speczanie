#include "args.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../files/open_files.h"


int process_args(const int argc, char** argv, Options* options_out) {
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--autoimport") == 0) {
            if (i + 2 >= argc) {
                printf("Usage: %s [files] --autoimport <x col> <y col>\n", argv[0]);
                return 1;
            }
            options_out->auto_import = true;

            const char char_x = argv[i + 1][0];
            const char char_y = argv[i + 2][0];
            if (!isdigit(char_x) || !isdigit(char_y)) {
                puts("Auto import columns have to be non-negative numbers");
                return 3;
            }
            const int x = char_x - '0';
            const int y = char_y - '0';
            if (x == y) {
                puts("Auto import columns can't be equal");
                return 3;
            }
            options_out->auto_import_x = x;
            options_out->auto_import_y = y;
            i += 2;
            continue;
        }
        if (open_file(argv[i]) == -1) return -1;
    }
    return 0;
}
