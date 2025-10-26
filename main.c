#include <raylib.h>
#include <stdio.h>

#include "data/parse_binary.h"
#include "data/point_data.h"
#include "diagnostics/more_data.h"
#include "diagnostics/components/Clock.h"
#include "diagnostics/components/FpsCounter.h"
#include "plot/move.h"
#include "plot/plot_math.h"
#include "plot/components/DataPlot.h"
#include "plot/components/Grid.h"
#include "plot/components/SplinePlot.h"
#include "text/Button.h"
#include "text/text.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Raylib Window");
    font_init("resources/JetBrainsMono-SemiBold.ttf");

    // BinaryFile file = file_parse("input/19_v10.W01");
    BinaryFile file = file_parse("input/20_v50.W01");
    DataSource file_source = data_source_columns(&file, 3, 0, 50.f);
    DataPlotState plot_state = DataPlotState_create(file_source.count);

    MoveState move_state = {
        .zoom = 1.f,
        .pan = {0, 0}
    };
    move_change_t change = 0b11;

    int clicks = 0;
    char clicks_text[4] = "0";

    while (!WindowShouldClose()) {
        const Bounds bounds = compute_bounds(move_state.zoom, move_state.pan);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        const button_state_t button = Button((TextBoxProps) {
            .origin = {10, 100},
            .padding = {20, 10},
            .text = "chuj",
            .font_size = 20,
            .background_color = {255, 230, 230, 255},
            .border_color = BLACK,
            .border = 2
        }, (TextBoxProps) {
            .padding = {20, 10},
            .text = clicks_text,
            .font_size = 20,
            .background_color = LIGHTGRAY,
            .border_color = PINK,
            .border = 10
        });
        if (button == BUTTON_STATE_CLICKED) {
            sprintf(clicks_text, "%d", ++clicks);
        }

        Grid(bounds);

        DataPlot(
            (DataPlotProps) {
                .data_source = file_source,
                .bounds = bounds,
                .plot_offset = move_state.plot_offset
            },
            change, &plot_state);

        if (GetTime() > .5) FpsCounter();
        EndDrawing();

        change = process_move(&move_state, bounds);
    }

    font_unload();
    CloseWindow();
    file_destroy(&file);
    data_source_destroy(&file_source);
    DataPlotState_destroy(&plot_state);
}
