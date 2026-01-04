#ifndef OPEN_FILES_H
#define OPEN_FILES_H

#include "../data/parse_binary.h"
#include "../data/data_source.h"
#include "../plot/components/DataPlot.h"

typedef struct {
    BinaryFile binary_file;
    DataSource data_source;
    DataPlotState data_plot_state;
    char* filename;
} OpenFile;

OpenFile* get_files();
int get_count();

void select_file(int index);
OpenFile* get_selected_file();

int open_file(const char* filename);
void close_file(int index);
void clear_files();

#endif //OPEN_FILES_H
