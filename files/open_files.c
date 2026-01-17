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

enum FileType determine_file_type(const char* filename) {
    const size_t len = strlen(filename);
    if ( filename[len - 4]       != '.') return FILE_TYPE_W01;
    if ((filename[len - 3] | 32) != 'c') return FILE_TYPE_W01;
    if ((filename[len - 2] | 32) != 's') return FILE_TYPE_W01;
    if ((filename[len - 1] | 32) != 'v') return FILE_TYPE_W01;
    return FILE_TYPE_CSV;
}

int open_file(const char* filename) {
    if (count == OPEN_FILES_MAX_COUNT) return -1;
    const enum FileType file_type = determine_file_type(filename);

    if (file_type == FILE_TYPE_W01) {
        const union FileParseResult parse_result = file_parse(filename);
        if (is_parsed_error(parse_result)) {
            printf("%s: ", filename);
            print_parse_error(parse_result.error);
            return -1;
        }

        files[count].binary_file = parse_result.file;
        files[count].data_source = data_source_columns(&files[count].binary_file, 3, 2);
    }
    else {
        const union CsvParseResult parse_result = csv_parse(filename);
        if (is_csv_error(parse_result)) {
            printf("Error %s: ", filename);
            return -1;
        }

        files[count].csv_file = parse_result.file;
        files[count].data_source = (DataSource) {
            .data = parse_result.file.data,
            .count = parse_result.file.count
        };
    }
    files[count].file_type = file_type;
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
    char* csv_name;
    if (open_file->file_type == FILE_TYPE_CSV) {
        csv_name = open_file->filepath;
    }
    else {
        const size_t filepath_size = strlen(open_file->filepath);
        csv_name = malloc(filepath_size + 5);
        strcpy(csv_name, open_file->filepath);
        csv_name[filepath_size    ] = '.';
        csv_name[filepath_size + 1] = 'c';
        csv_name[filepath_size + 2] = 's';
        csv_name[filepath_size + 3] = 'v';
        csv_name[filepath_size + 4] = '\0';
    }

    FILE* csv_file = fopen(csv_name, "w");
    printf("Exporting to %s\n", csv_name);

    if (open_file->file_type != FILE_TYPE_CSV) free(csv_name);

    if (!csv_file) {
        puts("Cannot open file");
        return 0;
    }
    int bytes_written = fprintf(csv_file, "a\ntime,load\n");
    for (int i = 0; i < open_file->data_source.count; ++i) {
        const Vector2 row = open_file->data_source.data[i];
        bytes_written += fprintf(csv_file, "%f,%f\n", row.x, row.y);
    }
    fclose(csv_file);
    printf("%d\n", bytes_written);
    return bytes_written;
}
