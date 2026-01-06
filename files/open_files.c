#include "open_files.h"

#include <stdlib.h>
#include <string.h>

#define OPEN_FILES_MAX_COUNT 10

OpenFile files[OPEN_FILES_MAX_COUNT];
int count = 0;
int selected = 0;

OpenFile* get_files() {
    return files;
}

int get_count() {
    return count;
}

int get_selected() {
    return selected;
}

void select_file(const int index) {
    selected = index;
}

OpenFile* get_selected_file() {
    return &files[selected];
}

int open_file(const char* filename) {
    if (count == OPEN_FILES_MAX_COUNT) return -1;

    files[count].binary_file = file_parse(filename);
    files[count].data_source = data_source_columns(&files[count].binary_file, 3, 0, 100.f);
    files[count].data_plot_state = DataPlotState_create(files[count].data_source.count);
    files[count].filename = malloc(strlen(filename) + 1);
    strcpy(files[count].filename, filename);
    return count++;
}

void free_file(const int index) {
    file_destroy(&files[index].binary_file);
    data_source_destroy(&files[index].data_source);
    DataPlotState_destroy(&files[index].data_plot_state);
    free(files[index].filename);
}

void clear_files() {
    for (int i = 0; i < count; ++i) {
        free_file(i);
    }
}
