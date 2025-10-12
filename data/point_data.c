#include "point_data.h"

void translate_data_to_points(const Vector2* data, Vector2* points, const int count, const Bounds bounds) {
    const float x_factor =  1 / (bounds.end_x - bounds.start_x) * PLOT_WIDTH;
    const float y_factor = -1 / (bounds.end_y - bounds.start_y) * PLOT_HEIGHT;
    for (int i = 0; i < count; i++) {
        points[i].x = (data[i].x - bounds.start_x) * x_factor + PLOT_OFFSET_X;
        points[i].y = (data[i].y + bounds.start_y) * y_factor + PLOT_OFFSET_Y;
    }
}