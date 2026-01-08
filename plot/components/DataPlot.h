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

enum PlotInputState {
    PLOT_INPUT_IDLE,
    PLOT_INPUT_MOVE,
    PLOT_INPUT_SELECT,
};

typedef struct {
    Vector2* point_buffer;
    Vector2* shadow_point_buffer;
    VisiblePointsInfo visible;
    VisiblePointsInfo shadow_visible;
    char count_text[32];
    int selected_point;

    Vector2 pan;
    Vector2 plot_offset;
    float zoom;
    enum PlotInputState input_state;

} DataPlotState;

typedef struct {
    DataSource data_source;
    Bounds bounds;
} DataPlotProps;

void DataPlot(DataPlotProps props, move_change_t change, DataPlotState* state);

DataPlotState DataPlotState_create(int data_count);
void DataPlotState_destroy(DataPlotState* state);

#endif //DATAPLOT_H
