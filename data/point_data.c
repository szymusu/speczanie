#include "point_data.h"

// zakładamy, że data.x rośnie, będzie to prawda dla każdej funkcji
int find_first_visible(const Vector2* data, const int count, const float start_x) {
    if (data[count - 1].x < start_x) return -1;

    int a = 0, b = count - 1;
    while (b - a > 1) {
        const int mid = (a + b) / 2;
        if (data[mid].x > start_x) b = mid;
        else a = mid;
    }
    return a;
}

int translate_data_to_points(const DataSource data_source, Vector2* point_buffer, const Bounds bounds, const Vector2 offset) {
    const int start = find_first_visible(data_source.data, data_source.count, bounds.start_x - offset.x);
    if (start == -1) return 0;

    const float x_factor =  1 / (bounds.end_x - bounds.start_x) * PLOT_WIDTH;
    const float y_factor = -1 / (bounds.end_y - bounds.start_y) * PLOT_HEIGHT;

    int visible_count = data_source.count - start;
    for (int i = 0; i < visible_count; i++) {
        if (data_source.data[i + start].x > bounds.end_x - offset.x) {
            return i;
        }
        point_buffer[i].x = (data_source.data[i + start].x - bounds.start_x + offset.x) * x_factor + PLOT_OFFSET_X;
        point_buffer[i].y = (data_source.data[i + start].y + bounds.start_y - offset.y) * y_factor + PLOT_OFFSET_Y;
    }
    return visible_count;
}