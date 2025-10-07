#include "parse_binary.h"

#include <stdio.h>
#include <stdlib.h>

BinaryFile file_parse(const char* filename) {
    BinaryFile data;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return (BinaryFile) {0};
    }
    fread(&data.header, sizeof(data.header), 1, file);

    data.columns = malloc(sizeof(data.columns[0]) * data.header.column_count);
    for (int i = 0; i < data.header.column_count; ++i) {
        fread(&data.columns[i], sizeof(data.columns[0].pre_data) + sizeof(data.columns[0].label), 1, file);
        data.columns[i].data = malloc(4 * data.header.row_count);
        fread(data.columns[i].data, 4, data.header.row_count, file);
    }

    return data;
}

void column_destroy(Column* column) {
    free(column->data);
}

void file_destroy(BinaryFile* file) {
    for (uint32_t i = 0; i < file->header.column_count; ++i) {
        column_destroy(&file->columns[i]);
    }
    free(file->columns);
}

void column_print(Column* column, const uint32_t count) {
    printf("Pre data %d\nLabel %.59s\n", column->pre_data, column->label);
    for (uint32_t i = 0; i < count; ++i) {
        printf("%f, ", column->data[i]);
    }
    puts("");
}

void file_header_print(FileHeader* header) {
    printf("Magic 0x%x\n"
           "V1 %d\n"
           "Size %d\n"
           "Name %.8s\n"
           "Rows %d\n"
           "Columns %d\n"
           "DateTime %.18s\n"
           "Program %s\n",
           header->magic,
           header->version,
           header->size,
           header->name,
           header->row_count,
           header->column_count,
           header->datetime,
           header->program_name
           );
}
