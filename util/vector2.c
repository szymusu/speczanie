#include "vector2.h"

#include <math.h>
#include <stdint.h>

bool is_vec2_zero(Vector2 vec) {
    return *(uint64_t*)&vec == 0;
}

float vec2_magnitude(const Vector2 vec) {
    return sqrtf(vec.x*vec.x + vec.y*vec.y);
}
