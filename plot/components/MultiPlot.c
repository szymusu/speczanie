#include "MultiPlot.h"

#include "../../files/open_files.h"

void MultiPlot(MultiPlotState* state, MultiPlotProps props) {
    OpenFile* files = get_files();
    const int count = get_count();

    for (int i = 0; i < count; ++i) {
        if (!is_imported(&files[i])) continue;

        DataPlot(
            (DataPlotProps) {
                .data_source = files[i].data_source,
                .bounds = props.bounds,
                .color = COLORS[i & 7]
            },
            1, &files[i].data_plot_state);
    }
}
