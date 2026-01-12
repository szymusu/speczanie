#ifndef SWAPBACK_ARRAY_H
#define SWAPBACK_ARRAY_H
#include <stddef.h>

typedef struct SBArray {
    int* data;
    size_t count;
} SBArray;

SBArray sb_array_create(size_t capacity);
void sb_array_destroy(SBArray array);
int sb_array_add(int value);

#endif //SWAPBACK_ARRAY_H