#include "Grid.h"

#include <raylib.h>
#include <stdio.h>

#include "../plot_math.h"
#include "../../text/text.h"

float find_step(const Bounds bounds) {
    const float target_step = (bounds.end_x - bounds.start_x) / 10.f;
    float step = 1.f;
    if (step > target_step) {
        while (step > target_step) {
            step /= 2.f;
        }
    }
    else {
        while (step < target_step) {
            step *= 2.f;
        }
    }
    return step;
}

void Grid(const Bounds bounds) {
    const float step = find_step(bounds);

    DrawLineEx(
        (Vector2) {transform_x_to_pixelf(0, bounds.start_x, bounds.end_x), PLOT_OFFSET_Y},
        (Vector2) {transform_x_to_pixelf(0, bounds.start_x, bounds.end_x), PLOT_HEIGHT + PLOT_OFFSET_Y},
        1.5f, BLACK
        );
    DrawLineEx(
        (Vector2) {PLOT_OFFSET_X, transform_y_to_pixelf(0, bounds.start_y, bounds.end_y)},
        (Vector2) {PLOT_WIDTH + PLOT_OFFSET_X, transform_y_to_pixelf(0, bounds.start_y, bounds.end_y)},
        1.5f, BLACK
        );

    char number_text[16];
    const int zero_x = transform_x_to_pixel(0, bounds.start_x, bounds.end_x);
    const int zero_y = transform_y_to_pixel(0, bounds.start_y, bounds.end_y);

    Vector2 start = {.y = PLOT_OFFSET_Y};
    Vector2 end = {.y = PLOT_HEIGHT + PLOT_OFFSET_Y};
    for (float x = 0.; x <= bounds.end_x; x += step) {
        const float px = transform_x_to_pixelf(x, bounds.start_x, bounds.end_x);
        start.x = px;
        end.x = px;
        DrawLineEx(start, end, 1.f, GRAY);
        sprintf(number_text, "%.2f", x);
        Text(number_text, (int) px, zero_y, 12, BLACK);
    }
    for (float x = -step; x >= bounds.start_x; x -= step) {
        const float px = transform_x_to_pixelf(x, bounds.start_x, bounds.end_x);
        start.x = px;
        end.x = px;
        DrawLineEx(start, end, 1.f, GRAY);
        sprintf(number_text, "%.2f", x);
        Text(number_text, (int) px, zero_y, 12, BLACK);
    }
    start.x = PLOT_OFFSET_X;
    end.x = PLOT_WIDTH + PLOT_OFFSET_X;
    for (float y = step;; y += step) {
        const float py = transform_y_to_pixelf(y, bounds.start_y, bounds.end_y);
        if (py < PLOT_OFFSET_Y) break;
        start.y = py;
        end.y = py;
        DrawLineEx(start, end, 1.f, GRAY);
        sprintf(number_text, "%.2f", y);
        Text(number_text, zero_x, (int) py, 12, BLACK);
    }
    for (float y = -step;; y -= step) {
        const float py = transform_y_to_pixelf(y, bounds.start_y, bounds.end_y);
        if (py > PLOT_OFFSET_Y + PLOT_HEIGHT) break;
        start.y = py;
        end.y = py;
        DrawLineEx(start, end, 1.f, GRAY);
        sprintf(number_text, "%.2f", y);
        Text(number_text, zero_x, (int) py, 12, BLACK);
    }
}
