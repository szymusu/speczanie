#ifndef MOVE_H
#define MOVE_H

#include "../types/types.h"

typedef struct {
    ViewMove* view_move;
    PlotMove* plot_move;
    Bounds bounds;

} MoveProps;

move_change_t process_move(MoveProps props);

#endif //MOVE_H
