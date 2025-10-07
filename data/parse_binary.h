#ifndef PARSE_BINARY_H
#define PARSE_BINARY_H

#include <stdint.h>

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t size;
    uint32_t zero1;
    char name[8];
    uint32_t size16;
    uint32_t row_count;
    uint32_t column_count;
    uint32_t one1;
    uint32_t one2;
    char datetime[18];
    char unknown1[42];
    char program_name[104];

} FileHeader;

typedef struct {
    uint32_t pre_data;
    char label[59];
    float* data;
} Column;

typedef struct {
    FileHeader header;
    Column* columns;
} BinaryFile;

/**
 * Call file_destroy() to clean up
 */
BinaryFile file_parse(const char* filename);
void file_header_print(FileHeader* header);
void column_print(Column* column, uint32_t count);
void file_destroy(BinaryFile* file);


#endif //PARSE_BINARY_H
