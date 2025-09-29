#include "Grid.h"

#include <raylib.h>
#include <stdio.h>

#include "../plot_math.h"

float transform_x_to_pixel(double x, double start_x, double end_x) {
    return (x - start_x) / (end_x - start_x) * PLOT_WIDTH + PLOT_OFFSET_X;
}

float transform_y_to_pixel(double y, double start_y, double end_y) {
    return (-y - start_y) / (end_y - start_y) * PLOT_HEIGHT + PLOT_OFFSET_Y;
}

void Grid(const double step) {
    const double start_x = PLOT_START_X;
    const double end_x = PLOT_END_X;
    const double start_y = PLOT_START_Y;
    const double end_y = PLOT_END_Y;

    DrawLineEx(
        (Vector2) {transform_x_to_pixel(0, start_x, end_x), PLOT_OFFSET_Y},
        (Vector2) {transform_x_to_pixel(0, start_x, end_x), PLOT_HEIGHT + PLOT_OFFSET_Y},
        1.5f, BLACK
        );
    DrawLineEx(
        (Vector2) {PLOT_OFFSET_X, transform_y_to_pixel(0, start_y, end_y)},
        (Vector2) {PLOT_WIDTH + PLOT_OFFSET_X, transform_y_to_pixel(0, start_y, end_y)},
        1.5f, BLACK
        );

    Vector2 start = {.y = PLOT_OFFSET_Y};
    Vector2 end = {.y = PLOT_HEIGHT + PLOT_OFFSET_Y};
    char number[16];
    for (double x = 0.; x <= end_x; x += step) {
        const float px = transform_x_to_pixel(x, start_x, end_x);
        start.x = px;
        end.x = px;
        DrawLineEx(start, end, .5f, GRAY);
        sprintf(number, "%.2f", x);
        DrawText(number, px, transform_y_to_pixel(0, start_y, end_y), 10, BLACK);
    }
    for (double x = -step; x >= start_x; x -= step) {
        const float px = transform_x_to_pixel(x, start_x, end_x);
        start.x = px;
        end.x = px;
        DrawLineEx(start, end, .5f, GRAY);
        sprintf(number, "%.2f", x);
        DrawText(number, px, transform_y_to_pixel(0, start_y, end_y), 10, BLACK);
    }
    start.x = PLOT_OFFSET_X;
    end.x = PLOT_WIDTH + PLOT_OFFSET_X;
    for (double y = step; y <= end_y; y += step) {
        const float py = transform_y_to_pixel(y, start_y, end_y);
        start.y = py;
        end.y = py;
        DrawLineEx(start, end, .5f, GRAY);
        sprintf(number, "%.2f", y);
        DrawText(number, transform_x_to_pixel(0, start_x, end_x), py, 10, BLACK);
    }
    for (double y = -step; y >= start_y; y -= step) {
        const float py = transform_y_to_pixel(y, start_y, end_y);
        start.y = py;
        end.y = py;
        DrawLineEx(start, end, .5f, GRAY);
        sprintf(number, "%.2f", y);
        DrawText(number, transform_x_to_pixel(0, start_x, end_x), py, 10, BLACK);
    }
}
