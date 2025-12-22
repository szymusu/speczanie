#include "vector2.h"

#include <stdint.h>

bool is_vec2_zero(Vector2 vec) {
    return *(uint64_t*)&vec == 0;
}
