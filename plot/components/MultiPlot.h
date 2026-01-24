#ifndef SPECZANIE_MULTIPLOT_H
#define SPECZANIE_MULTIPLOT_H

#include "../../data/point_data.h"
#include "../../types/types.h"

typedef struct {
    PointCache point_cache;
    DataSource data_source;
} SinglePlot;

typedef struct {
    char* text_buffers[2];
    SinglePlot* plots;
    int plot_count;
    ViewMove view_move;
    float S0, L0;
    float S0_tmp, L0_tmp;
    int text_max_len;
    int text_lengths[2];
    unsigned char input_focus;
    char constants_text[64];
    bool enabled;

    CurvePolynomial curve;
    Vector2* regression_points;
    int regression_points_count;
    int selected1, selected2;
    int selected_plot;

} MultiPlotState;

typedef struct {
    Bounds bounds;
} MultiPlotProps;

void MultiPlot(MultiPlotProps props, MultiPlotState* state, move_change_t* change);

void MultiPlot_enable(MultiPlotState* state, ViewMove view_move);
ViewMove MultiPlot_disable(MultiPlotState* state);

#endif //SPECZANIE_MULTIPLOT_H