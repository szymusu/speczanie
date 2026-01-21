#include "autoimport.h"

#include <ctype.h>
#include <stdio.h>

int arg_autoimport(const int argc, char** argv, int* i, Options* options) {
    if (*i + 2 >= argc) {
        printf("Usage: %s [files] --autoimport <x col> <y col>\n", argv[0]);
        return 1;
    }
    options->auto_import = true;

    const char char_x = argv[*i + 1][0];
    const char char_y = argv[*i + 2][0];
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
    options->auto_import_x = x;
    options->auto_import_y = y;
    *i += 2;
    return 0;
}
