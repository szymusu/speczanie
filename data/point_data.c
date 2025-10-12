#include "point_data.h"

// zakładamy, że data.x rośnie, będzie to prawda dla każdej funkcji
int find_first_visible(const Vector2* data, const int count, const float start_x) {
    if (data[count - 1].x < start_x) return -1;

    // O(logn)
    int a = 0, b = count - 1, mid;
    while (b - a > 1) {
        mid = (a+b) / 2;
        if (data[mid].x > start_x) b = mid;
        else a = mid;
    }
    return a;

    // O(n)
    // for (int i = 0; i < count; ++i) {
    //     if (data[i].x >= start_x) {
    //         return i;
    //     }
    // }
    // return -1;
}

int translate_data_to_points(const Vector2* data, Vector2* points, const int count, const Bounds bounds) {
    const int start = find_first_visible(data, count, bounds.start_x);
    if (start == -1) return 0;

    const float x_factor =  1 / (bounds.end_x - bounds.start_x) * PLOT_WIDTH;
    const float y_factor = -1 / (bounds.end_y - bounds.start_y) * PLOT_HEIGHT;

    for (int i = 0; i < count - start; i++) {
        if (data[i + start].x > bounds.end_x) {
            return i;
        }
        points[i].x = (data[i + start].x - bounds.start_x) * x_factor + PLOT_OFFSET_X;
        points[i].y = (data[i + start].y + bounds.start_y) * y_factor + PLOT_OFFSET_Y;
    }
    return count - start;
}