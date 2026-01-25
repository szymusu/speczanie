#include "args.h"

#include <string.h>

#include "autoimport.h"
#include "help.h"
#include "../files/open_files.h"

int process_args(const int argc, char** argv, Options* options_out) {
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 256;
        }

        if (strcmp(argv[i], "--autoimport") == 0) {
            const int error = arg_autoimport(argc, argv, &i, options_out);
            if (error) return error;
            continue;
        }

        if (strcmp(argv[i], "--fps") == 0) {
            options_out->show_fps = true;
            continue;
        }

        if (strcmp(argv[i], "--vsync") == 0) {
            options_out->enable_vsync = true;
            continue;
        }

        if (strcmp(argv[i], "--msaa") == 0) {
            options_out->enable_msaa = true;
            continue;
        }

        if (open_file(argv[i]) == -1) return -1;
    }
    return 0;
}
