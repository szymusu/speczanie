#ifndef SPECZANIE_MULTIPLOT_H
#define SPECZANIE_MULTIPLOT_H

#include "../../data/point_data.h"
#include "../../types/types.h"

typedef struct {
    PointCache point_cache;
    DataSource data_source;
} SinglePlot;

typedef struct {
    SinglePlot* plots;
    int plot_count;

    ViewMove view_move;
    bool enabled;

} MultiPlotState;

typedef struct {
    Bounds bounds;
} MultiPlotProps;

void MultiPlot(MultiPlotProps props, MultiPlotState* state, move_change_t change);

void MultiPlot_enable(MultiPlotState* state, ViewMove view_move);
ViewMove MultiPlot_disable(MultiPlotState* state);

#endif //SPECZANIE_MULTIPLOT_H