#include "data_source.h"

#include <stdlib.h>
#include <string.h>


DataSource data_source_columns(const BinaryFile* file, const int x_column, const int y_column) {
    const int count = file->header.row_count;
    DataSource data_source = {
        .count = count,
        .data = malloc(sizeof(Vector2) * count)
    };
    data_source.base = data_source.data;

    const bool is_reverse = file->columns[x_column].data[0] > file->columns[x_column].data[count - 1];

    for (int i = 0; i < count; ++i) {
        const int data_index = is_reverse ? count - i - 1 : i;
        data_source.data[i].x = file->columns[x_column].data[data_index];
        data_source.data[i].y = file->columns[y_column].data[data_index];
    }
    return data_source;
}

void data_source_destroy(DataSource* data_source) {
    free(data_source->base);
}

char* axis_label_trim(const BinaryFile* binary_file, const int column) {
    char* label = binary_file->columns[column].label;
    char* spaces = strchr(label, ' ');
    if (!spaces) return label;

    char* unit = spaces;
    while (*unit == ' ' && *unit) unit++;
    if (!*unit) {
        *spaces = 0;
        return label;
    }

    char* second_spaces = strchr(unit, ' ');
    if (!second_spaces) return label;

    second_spaces[0] = ']';
    second_spaces[1] = 0;
    strcpy(spaces + 2, unit);
    spaces[1] = '[';
    return label;
}
