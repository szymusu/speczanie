#ifndef SPECZANIE_MULTIPLOT_H
#define SPECZANIE_MULTIPLOT_H

#include "../plot_math.h"

typedef struct {
    ViewMove view_move;
    bool enabled;
} MultiPlotState;

typedef struct {
    Bounds bounds;
} MultiPlotProps;

void MultiPlot(MultiPlotState* state, MultiPlotProps props);

#endif //SPECZANIE_MULTIPLOT_H