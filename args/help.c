#include "help.h"

#include <stdio.h>

void print_help(const char* program_name) {
    printf("Usage: %s [files] [options]\n", program_name);
    puts("Options:");
    puts("\t --help \n\t\t Print this help message and exit.\n");
    puts("\t --autoimport <x col> <y col> \n\t\t Automatically choose columns while importing W01 files.\n");
    puts("\t --fps \n\t\t Show FPS counter in top left corner of the screen.\n");
    puts("\t --vsync \n\t\t Enable V-Sync.\n");
    puts("\t --msaa \n\t\t Enable 4x MSAA anti-aliasing.\n");
}
