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