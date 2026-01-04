#ifndef VECTOR2_H
#define VECTOR2_H

#include <raylib.h>
#include <stdbool.h>

#define VECTOR2_ZERO (Vector2) {0,0}

bool is_vec2_zero(Vector2 vec);
float vec2_magnitude(Vector2 vec);
float vec2_angle(Vector2 vec);
float vec2_angle_between(Vector2 v1, Vector2 v2);

#endif //VECTOR2_H
