#ifndef CONTROLS_H
#define CONTROLS_H

#include "MultiPlot.h"
#include "../../files/open_files.h"

move_change_t Controls(OpenFile* current_file, DataPlotState* data_plot_state, MultiPlotState* multi_plot_state, move_change_t change);

#endif //CONTROLS_H
