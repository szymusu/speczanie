#ifndef CONTROLS_H
#define CONTROLS_H

#include "MultiPlot.h"
#include "../../files/open_files.h"

typedef struct {
    OpenFile* current_file;
    MultiPlotState* multi_plot_state;
    Bounds bounds;
    move_change_t change;
} ControlsProps;

move_change_t Controls(ControlsProps props);

#endif //CONTROLS_H
