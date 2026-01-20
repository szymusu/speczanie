#ifndef SPECZANIE_MULTICONTROLS_H
#define SPECZANIE_MULTICONTROLS_H

#include "MultiPlot.h"

typedef struct {
    MultiPlotState* state;
    ViewMove* plot_move;
    move_change_t change;

} MultiControlProps;

move_change_t MultiControls(MultiControlProps props);

#endif //SPECZANIE_MULTICONTROLS_H