#include "args.h"

#include "../files/open_files.h"

int process_args(const int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if (open_file(argv[i]) == -1) return -1;
    }
    return 0;
}
