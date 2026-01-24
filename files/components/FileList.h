#ifndef FILELIST_H
#define FILELIST_H
#include <stdbool.h>

typedef struct {
    int selected;
    int closed;
} FileListChange;

FileListChange FileList(bool is_multi);

#endif //FILELIST_H
