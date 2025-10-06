#ifndef PLOT_MATH_H
#define PLOT_MATH_H

#define PLOT_WIDTH 780
#define PLOT_HEIGHT 430
#define PLOT_OFFSET_X 10
#define PLOT_OFFSET_Y 10

#define PLOT_START_X -10.
#define PLOT_END_X 10.
#define PLOT_START_Y -10.
#define PLOT_END_Y 10.

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

Bounds compute_bounds(double zoom, double pan_x);

#endif //PLOT_MATH_H
