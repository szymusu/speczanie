#ifndef DATAPLOT_H
#define DATAPLOT_H

#include "../plot_math.h"
#include "../../data/data_source.h"
#include "../../data/point_data.h"
#include "../../data/operations/data_operation.h"
#include "../../types/types.h"

typedef struct DataPlotState {
    char* x_label;
    char* y_label;

    PointCache point_cache;
    PointCache shadow_cache;

    ViewMove view_move;
    PlotMove plot_move;

    int selected_point;
    int selected_second_point;

    CurveLinear curve_linear;
    CurvePolynomial curve_polynomial;
    Vector2* regression_points;
    int regression_points_count;

    DataOperationStack operation_stack;

} DataPlotState;

typedef struct DataPlotProps {
    DataSource data_source;
    Bounds bounds;
    Color color;

} DataPlotProps;

void DataPlot(DataPlotProps props, move_change_t change, DataPlotState* state);

DataPlotState DataPlotState_create(int data_count);
void DataPlotState_destroy(DataPlotState* state);

#endif //DATAPLOT_H
