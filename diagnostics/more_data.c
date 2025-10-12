#include "more_data.h"

#include <math.h>
#include <stdlib.h>

DataAndPoints create_sinus_data(const int count, const float offset) {
    DataAndPoints data = {
        .count = count,
        .data = malloc(sizeof(Vector2) * count),
        .points = malloc(sizeof(Vector2) * count),
    };
    for (int i = 0; i < count; i++) {
        data.data[i].x = i * .01f - 100000.f;
        data.data[i].y = sinf(data.data[i].x) + offset;
    }
    return data;
}

void destroy_sinus_data(DataAndPoints* data) {
    free(data->data);
    free(data->points);
}