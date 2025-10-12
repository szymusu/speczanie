#include "plot_math.h"

double pixel_to_x(const int pixel) {
    return (double) pixel / PLOT_WIDTH * (PLOT_END_X - PLOT_START_X) + PLOT_START_X;
}

int y_to_pixel(const double y) {
    return (int) ((y - PLOT_START_Y) / (PLOT_END_Y - PLOT_START_Y) * PLOT_HEIGHT);
}

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

Bounds compute_bounds(const float zoom, const Vector2 pan) {
    return (Bounds) {
        .start_x = PLOT_START_X / zoom + pan.x,
        .end_x = PLOT_END_X / zoom + pan.x,
        .start_y = PLOT_START_Y / zoom / ((float) PLOT_WIDTH / PLOT_HEIGHT) + pan.y,
        .end_y = PLOT_END_Y / zoom / ((float) PLOT_WIDTH / PLOT_HEIGHT) + pan.y,
    };
}
