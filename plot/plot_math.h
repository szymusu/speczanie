#ifndef PLOT_MATH_H
#define PLOT_MATH_H

#define PLOT_WIDTH 800
#define PLOT_HEIGHT 450
#define PLOT_OFFSET_X 0
#define PLOT_OFFSET_Y 0

#define PLOT_START_X -10.
#define PLOT_END_X 10.
#define PLOT_START_Y -10.
#define PLOT_END_Y 10.

#include <raylib.h>

typedef struct {
    double start_x;
    double end_x;
    double start_y;
    double end_y;
} Bounds;

double pixel_to_x(int pixel);

int y_to_pixel(double y);

float transform_x_to_pixelf(double x, double start_x, double end_x);
float transform_y_to_pixelf(double y, double start_y, double end_y);
int transform_x_to_pixel(double x, double start_x, double end_x);
int transform_y_to_pixel(double y, double start_y, double end_y);
Vector2 transform_v_to_pixel(Vector2 v, Bounds bounds);

Bounds compute_bounds(double zoom, Vector2 pan);

#endif //PLOT_MATH_H
