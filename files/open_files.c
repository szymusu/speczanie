#include "open_files.h"

#include <stdio.h>
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

OpenFile* select_file(const int index) {
    selected = index;
    return &files[selected];
}

OpenFile* get_selected_file() {
    if (!count) return NULL;
    return &files[selected];
}

void set_path_and_name(OpenFile* file, const char* filepath) {
    int length = 0;
    int last_slash = 0;
    for (int i = 0;; ++i) {
        if (filepath[i] == '\0') {
            length = i;
            break;
        }
        if (filepath[i] == '/') {
            last_slash = i;
        }
    }
    char* path = malloc(length + 1);
    strcpy(path, filepath);

    char* name;
    if (length - last_slash < 1) {
        name = path;
    }
    else {
        name = &path[last_slash + 1];
    }

    file->filepath = path;
    file->filename = name;
}

int open_file(const char* filename) {
    if (count == OPEN_FILES_MAX_COUNT) return -1;

    const union FileParseResult parse_result = file_parse(filename);
    if (is_parsed_error(parse_result)) {
        printf("%s: ", filename);
        print_parse_error(parse_result.error);
        return -1;
    }

    files[count].binary_file = parse_result.file;
    files[count].data_source = data_source_columns(&files[count].binary_file, 3, 2);
    files[count].data_plot_state = DataPlotState_create(files[count].data_source.count);
    files[count].data_plot_state.scale_x = fit_scale(files[count].data_source.data[0].x, files[count].data_source.data[files[count].data_source.count - 1].x);
    set_path_and_name(&files[count], filename);

    return count++;
}

void free_file(const int index) {
    file_destroy(&files[index].binary_file);
    data_source_destroy(&files[index].data_source);
    DataPlotState_destroy(&files[index].data_plot_state);
    free(files[index].filepath);
}

void clear_files() {
    for (int i = 0; i < count; ++i) {
        free_file(i);
    }
}

int file_export_csv(const OpenFile* open_file) {
    const size_t filepath_size = strlen(open_file->filepath);
    char* csv_name = malloc(filepath_size + 5);
    strcpy(csv_name, open_file->filepath);
    csv_name[filepath_size    ] = '.';
    csv_name[filepath_size + 1] = 'c';
    csv_name[filepath_size + 2] = 's';
    csv_name[filepath_size + 3] = 'v';
    csv_name[filepath_size + 4] = '\0';

    FILE* csv_file = fopen(csv_name, "w");
    printf("Exporting to %s\n", csv_name);
    free(csv_name);
    if (!csv_file) {
        puts("Cannot open file");
        return 0;
    }
    int bytes_written = fprintf(csv_file, "time,load\n");
    for (int i = 0; i < open_file->data_source.count; ++i) {
        const Vector2 row = open_file->data_source.data[i];
        bytes_written += fprintf(csv_file, "%f,%f\n", row.x, row.y);
    }
    fclose(csv_file);
    printf("%d\n", bytes_written);
    return bytes_written;
}
