#ifndef MOVE_H
#define MOVE_H

#include <raylib.h>

#include "plot_math.h"

typedef unsigned char move_change_t;

move_change_t process_move(float* zoom, Vector2* pan, Bounds bounds);

#endif //MOVE_H
