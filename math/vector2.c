#include "vector2.h"

#include <math.h>

bool is_vec2_zero(const Vector2 vec) {
    return vec.x == 0 && vec.y == 0;
}

float vec2_magnitude(const Vector2 vec) {
    return sqrtf(vec.x*vec.x + vec.y*vec.y);
}

float vec2_angle(const Vector2 vec) {
    return atan2f(vec.y, vec.x);
}

float vec2_angle_between(const Vector2 v1, const Vector2 v2) {
    return atan2f(v2.y - v1.y, v2.x - v1.x);
}

Vector2 vec2_subtract(const Vector2 this, const Vector2 from_this) {
    return (Vector2) {
        from_this.x - this.x,
        from_this.y - this.y
    };
}
