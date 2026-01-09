#ifndef DATAPLOT_H
#define DATAPLOT_H

#include "../plot_math.h"
#include "../../data/data_source.h"
#include "../../data/point_data.h"

#define MOVE_CHANGE_ZOOM 1
#define MOVE_CHANGE_PAN 2
#define MOVE_CHANGE_PLOT 4
#define MOVE_CHANGE_APPLY_OFFSET 8

typedef unsigned char move_change_t;

enum PlotInputMode {
    PLOT_INPUT_IDLE,
    PLOT_INPUT_MOVE,
    PLOT_INPUT_SELECT,
};

typedef struct {
    Vector2 end_point;
    float a;
    float b;
} CurveLinear;

typedef struct {
    Vector2* point_buffer;
    Vector2* shadow_point_buffer;
    VisiblePointsInfo visible;
    VisiblePointsInfo shadow_visible;

    Vector2 pan;
    Vector2 plot_offset;
    float zoom;

    Vector2 mouse_position;
    int selected_point;
    int selected_second_point;

    CurveLinear curve_linear;

    enum PlotInputMode input_mode;

} DataPlotState;

typedef struct {
    DataSource data_source;
    Bounds bounds;
} DataPlotProps;

void DataPlot(DataPlotProps props, move_change_t change, DataPlotState* state);

DataPlotState DataPlotState_create(int data_count);
void DataPlotState_destroy(DataPlotState* state);

#endif //DATAPLOT_H
