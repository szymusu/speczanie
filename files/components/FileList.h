#ifndef FILELIST_H
#define FILELIST_H
#include <stdbool.h>

typedef struct {
    int selected;
    int closed;
} FileListChange;

FileListChange FileList(bool show_colors);

#endif //FILELIST_H
