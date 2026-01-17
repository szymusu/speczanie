#include "parse_csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define DATA_START_CAPACITY 256

typedef struct {
    Vector2* data;
    int count;
    int capacity;
} Vector2DynamicArray;

Vector2DynamicArray da_create(const int start_capacity) {
    return (Vector2DynamicArray) {
        .data = malloc(start_capacity * sizeof (Vector2)),
        .count = 0,
        .capacity = start_capacity
    };
}

int da_push(Vector2DynamicArray* array, const Vector2 value) {
    array->count++;
    if (array->count == array->capacity) {
        array->capacity *= 2;
        Vector2* new_buffer = realloc(array->data, array->capacity * sizeof (Vector2));
        if (!new_buffer) return 1;
        array->data = new_buffer;
    }
    array->data[array->count - 1] = value;
    return 0;
}

void csv_error_expected(union CsvParseResult* res, const enum CsvParseErrorType type, const uint32_t expected, const uint32_t actual) {
    res->error.is_success = 0;
    res->error.error_type = type;
    res->error.expected_value = expected;
    res->error.actual_value = actual;
}

void csv_error(union CsvParseResult* res, const enum CsvParseErrorType type) {
    csv_error_expected(res, type, 0, 0);
}

union CsvParseResult csv_parse(const char* filename) {
    union CsvParseResult res = {0};
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        csv_error(&res, CSV_INVALID_HANDLE);
        return res;
    }

    char line_buffer[MAX_LINE_LENGTH];
    Vector2DynamicArray data = da_create(DATA_START_CAPACITY);

    int line_number = 0;
    while (fgets(line_buffer, MAX_LINE_LENGTH, file)) {
        line_number++;
        const char last_char = line_buffer[MAX_LINE_LENGTH - 2];
        if (last_char != '\0' && last_char != '\n') {
            csv_error(&res, LINE_TOO_LONG);
            free(data.data);
            return res;
        }
        if (!res.file.header) {
            res.file.header = malloc(MAX_LINE_LENGTH);
            memcpy(res.file.header, line_buffer, MAX_LINE_LENGTH);
            continue;
        }
        if (line_number == 2) continue;

        char* end_of_first;
        const float x = strtof(line_buffer, &end_of_first);
        const float y = strtof(end_of_first + 1, NULL);
        const int push_error = da_push(&data, (Vector2) {x, y});

        if (push_error) {
            free(res.file.header);
            free(data.data);
            csv_error(&res, OUT_OF_MEMORY);
            return res;
        }
    }
    fclose(file);

    res.file.data = data.data;
    res.file.count = data.count;

    float sum = 0;
    for (int i = 0; i < res.file.count; ++i) {
        sum += res.file.data[i].y;
    }
    printf("%f\n", sum);

    return res;
}

bool is_csv_error(const union CsvParseResult parse_result) {
    return parse_result.error.is_success == 0;
}
