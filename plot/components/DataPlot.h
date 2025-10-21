#ifndef DATAPLOT_H
#define DATAPLOT_H

#include "../plot_math.h"
#include "../move.h"
#include "../../data/data_source.h"

typedef struct {
    Vector2* point_buffer;
    int visible_count;
    char count_text[32];
    int visible_start;

} DataPlotState;

typedef struct {
    DataSource data_source;
    Bounds bounds;
    Vector2 plot_offset;
} DataPlotProps;

void DataPlot(DataPlotProps props, move_change_t change, DataPlotState* state);

DataPlotState DataPlotState_create(int data_count);
void DataPlotState_destroy(DataPlotState* state);

#endif //DATAPLOT_H
