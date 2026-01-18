#include "image_export.h"

#include "../math/vector2.h"

void image_export(const DataSource data_source, const char* filename) {
    if (data_source.count < 2) return;

    Image image = GenImageColor(PLOT_WIDTH, PLOT_HEIGHT, RAYWHITE);

    float min_y = data_source.data[0].y;
    float max_y = data_source.data[0].y;
    for (int i = 1; i < data_source.count; ++i) {
        const float y = data_source.data[i].y;
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
    }
    const float padding_y = (max_y - min_y) / 8;

    const float min_x = data_source.data[0].x;
    const float max_x = data_source.data[data_source.count - 1].x;
    const float padding_x = (max_x - min_x) / 10;

    const Bounds image_bounds = {
        min_x - padding_x, max_x + padding_x,
        -max_y - padding_y, -min_y + padding_y
    };

    Vector2 prev_transformed = transform_v_to_pixel(data_source.data[0], image_bounds);
    ImageDrawLineEx(&image, prev_transformed, transform_v_to_pixel(data_source.data[1], image_bounds), 3, DARKBLUE);

    for (int i = 1; i < data_source.count; ++i) {
        const Vector2 current_transformed = transform_v_to_pixel(data_source.data[i], image_bounds);
        ImageDrawLineEx(&image, prev_transformed, current_transformed, 3, DARKBLUE);
        prev_transformed = current_transformed;
    }

    const Vector2 zero = transform_v_to_pixel(VECTOR2_ZERO, image_bounds);

    const Vector2 x_axis_start = { zero.x, 0 };
    const Vector2 x_axis_end = { zero.x, PLOT_HEIGHT };
    ImageDrawLineEx(&image, x_axis_start, x_axis_end, 3, GRAY);

    const Vector2 y_axis_start = { 0, zero.y };
    const Vector2 y_axis_end = { PLOT_WIDTH, zero.y };
    ImageDrawLineEx(&image, y_axis_start, y_axis_end, 3, GRAY);

    ExportImage(image, filename);
    UnloadImage(image);
}
