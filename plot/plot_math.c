#include "plot_math.h"

double pixel_to_x(const int pixel) {
    return (double) pixel / PLOT_WIDTH * (PLOT_END_X - PLOT_START_X) + PLOT_START_X;
}

int y_to_pixel(const double y) {
    return (int) ((y - PLOT_START_Y) / (PLOT_END_Y - PLOT_START_Y) * PLOT_HEIGHT);
}
