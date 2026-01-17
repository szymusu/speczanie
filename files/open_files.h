#ifndef OPEN_FILES_H
#define OPEN_FILES_H

#include "../data/parse_binary.h"
#include "../data/data_source.h"
#include "../data/parse_csv.h"
#include "../plot/components/DataPlot.h"

enum FileType {
    FILE_TYPE_W01,
    FILE_TYPE_CSV,
};

typedef struct {
    union {
        BinaryFile binary_file;
        CsvFile csv_file;
    };
    DataSource data_source;
    DataPlotState data_plot_state;
    char* filename;
    char* filepath;

    enum FileType file_type;
} OpenFile;

OpenFile* get_files();
int get_count();

OpenFile* select_file(int index);
OpenFile* get_selected_file();
int get_selected();

int open_file(const char* filename);
void close_file(int index);
void clear_files();
int file_export_csv(const OpenFile* open_file);

#endif //OPEN_FILES_H
