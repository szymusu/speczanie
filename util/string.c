#include "string.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char* strclone(const char* source) {
    const size_t length = strlen(source);
    char* cloned = malloc(length + 1);
    for (size_t i = 0; source[i]; ++i) {
        cloned[i] = source[i];
    }
    cloned[length] = 0;
    return cloned;
}

char* strclone_extend(const char* source, const unsigned int extend_by) {
    const size_t source_length = strlen(source);
    char* cloned = malloc(source_length + extend_by + 1);
    strcpy(cloned, source);
    return cloned;
}
