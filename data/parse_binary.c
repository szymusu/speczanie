#include "parse_binary.h"

#include <stdio.h>
#include <stdlib.h>

void parse_error_expected(union FileParseResult* res, const enum FileParseErrorType type, const uint32_t expected, const uint32_t actual) {
    res->error.zero = 0;
    res->error.error_type = type;
    res->error.expected_value = expected;
    res->error.actual_value = actual;
}

void parse_error(union FileParseResult* res, const enum FileParseErrorType type) {
    parse_error_expected(res, type, 0, 0);
}

union FileParseResult file_parse(const char* filename) {
    union FileParseResult res;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        parse_error(&res, INVALID_HANDLE);
        return res;
    }
    fread(&res.file.header, sizeof(res.file.header), 1, file);

    if (res.file.header.magic != FILE_MAGIC) {
        fclose(file);
        parse_error_expected(&res, INVALID_MAGIC, FILE_MAGIC, res.file.header.magic);
        return res;
    }

    res.file.columns = malloc(sizeof(res.file.columns[0]) * res.file.header.column_count);
    for (int i = 0; i < res.file.header.column_count; ++i) {
        fread(&res.file.columns[i], sizeof(res.file.columns[0].pre_data) + sizeof(res.file.columns[0].label), 1, file);
        res.file.columns[i].data = malloc(4 * res.file.header.row_count);
        fread(res.file.columns[i].data, 4, res.file.header.row_count, file);
    }

    fclose(file);
    return res;
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

bool is_parsed_error(const union FileParseResult parse_result) {
    return parse_result.error.zero == 0;
}

void print_parse_error(const FileParseError error) {
    switch (error.error_type) {
    case INVALID_HANDLE:
        printf("Cannot open the file\n");
        break;
    case INVALID_MAGIC:
        printf("Wrong magic number. Expected %x, got %x\n", error.expected_value, error.actual_value);
        break;
    }
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
