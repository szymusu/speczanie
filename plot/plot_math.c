#include "plot_math.h"

#include <math.h>

float transform_x_to_pixelf(double x, double start_x, double end_x) {
    return (x - start_x) / (end_x - start_x) * PLOT_WIDTH + PLOT_OFFSET_X;
}

float transform_y_to_pixelf(double y, double start_y, double end_y) {
    return (-y - start_y) / (end_y - start_y) * PLOT_HEIGHT + PLOT_OFFSET_Y;
}

int transform_x_to_pixel(double x, double start_x, double end_x) {
    return (x - start_x) / (end_x - start_x) * PLOT_WIDTH + PLOT_OFFSET_X;
}

int transform_y_to_pixel(double y, double start_y, double end_y) {
    return (-y - start_y) / (end_y - start_y) * PLOT_HEIGHT + PLOT_OFFSET_Y;
}

Vector2 transform_v_to_pixel(const Vector2 v, const Bounds bounds) {
    return (Vector2){
        .x = (v.x - bounds.start_x) / (bounds.end_x - bounds.start_x) * PLOT_WIDTH + PLOT_OFFSET_X,
        .y = (-v.y - bounds.start_y) / (bounds.end_y - bounds.start_y) * PLOT_HEIGHT + PLOT_OFFSET_Y,
    };
}

Bounds compute_bounds(const ViewMove view_move) {
    return (Bounds) {
        .start_x = PLOT_START_X / view_move.zoom / view_move.scale_x + view_move.pan.x,
        .end_x = PLOT_END_X / view_move.zoom / view_move.scale_x + view_move.pan.x,
        .start_y = PLOT_START_Y / view_move.zoom / ((float) PLOT_WIDTH / PLOT_HEIGHT) + view_move.pan.y,
        .end_y = PLOT_END_Y / view_move.zoom / ((float) PLOT_WIDTH / PLOT_HEIGHT) + view_move.pan.y,
    };
}

float fit_scale(const float x1, const float x2) {
    const float diff = fabsf(x1 - x2);
    return PLOT_END_X / diff;
}
