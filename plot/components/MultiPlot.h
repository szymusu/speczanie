#ifndef SPECZANIE_MULTIPLOT_H
#define SPECZANIE_MULTIPLOT_H

#include "../plot_math.h"

typedef struct {
    Vector2 pan;
    float zoom;
    float scale_x;

    bool enabled;
} MultiPlotState;

typedef struct {
    Bounds bounds;
} MultiPlotProps;

void MultiPlot(MultiPlotState* state, MultiPlotProps props);

#endif //SPECZANIE_MULTIPLOT_H