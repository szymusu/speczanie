#ifndef PARSE_BINARY_H
#define PARSE_BINARY_H

#include <stdbool.h>
#include <stdint.h>

#define FILE_MAGIC 0x3f866666
// #define FILE_MAGIC 0x3f866665

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


enum FileParseErrorType {
    INVALID_HANDLE,
    INVALID_MAGIC
};

typedef struct {
    int zero;
    enum FileParseErrorType error_type;
    uint32_t expected_value;
    uint32_t actual_value;
} FileParseError;

union FileParseResult {
    BinaryFile file;
    FileParseError error; // error if error.zero == 0
};

/**
 * Call file_destroy() to clean up
 */
union FileParseResult file_parse(const char* filename);
void file_header_print(FileHeader* header);
void column_print(Column* column, uint32_t count);
void file_destroy(BinaryFile* file);
bool is_parsed_error(union FileParseResult parse_result);
void print_parse_error(FileParseError error);


#endif //PARSE_BINARY_H
