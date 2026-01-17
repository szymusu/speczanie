#ifndef FILELIST_H
#define FILELIST_H

typedef struct {
    int selected;
    int closed;
} FileListChange;

FileListChange FileList();

#endif //FILELIST_H
