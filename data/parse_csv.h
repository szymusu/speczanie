#ifndef SPECZANIE_PARSE_CSV_H
#define SPECZANIE_PARSE_CSV_H

#include <raylib.h>
#include <stdint.h>

typedef struct  {
    char* header;
    Vector2* data;
    int count;
} CsvFile;

enum CsvParseErrorType {
    CSV_INVALID_HANDLE,
    OUT_OF_MEMORY,
    LINE_TOO_LONG
};

typedef struct {
    int is_success;
    enum CsvParseErrorType error_type;
    uint32_t expected_value;
    uint32_t actual_value;
} CsvParseError;

union CsvParseResult {
    CsvFile file;
    CsvParseError error; // error if error.is_success == 0
};

union CsvParseResult csv_parse(const char* filename);
bool is_csv_error(union CsvParseResult parse_result);

#endif //SPECZANIE_PARSE_CSV_H