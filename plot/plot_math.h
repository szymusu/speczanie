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

double pixel_to_x(int pixel);

int y_to_pixel(double y);

#endif //PLOT_MATH_H
