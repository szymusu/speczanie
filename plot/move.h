#ifndef MOVE_H
#define MOVE_H

#include <raylib.h>

#include "plot_math.h"

typedef unsigned char move_change_t;

typedef struct {
    Vector2 pan;
    float zoom;
} MoveState;

move_change_t process_move(MoveState* state, Bounds bounds);

#endif //MOVE_H
