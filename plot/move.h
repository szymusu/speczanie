#ifndef MOVE_H
#define MOVE_H

#include <raylib.h>

#include "plot_math.h"

#define MOVE_CHANGE_ZOOM 1
#define MOVE_CHANGE_PAN 2
#define MOVE_CHANGE_PLOT 4
#define MOVE_CHANGE_APPLY_OFFSET 8

typedef unsigned char move_change_t;

typedef struct {
    Vector2 pan;
    Vector2 plot_offset;
    float zoom;

} MoveState;

move_change_t process_move(MoveState* state, Bounds bounds);

#endif //MOVE_H
