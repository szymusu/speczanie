#include "op_flip_x.h"

OpFlipX do_flip_x(DataSource* data_source, OpFlipX op) {
    const int mid_i = data_source->count / 2;
    for (int i = 0; i < mid_i; ++i) {
        const int j = data_source->count - i - 1;
        const Vector2 tmp = data_source->data[i];
        data_source->data[i] = data_source->data[j];
        data_source->data[j] = tmp;
        data_source->data[i].x = -data_source->data[i].x;
        data_source->data[j].x = -data_source->data[j].x;
    }
    if (data_source->count & 1) {
        data_source->data[mid_i].x = -data_source->data[mid_i].x;
    }
    return op;
}

void undo_flip_x(DataSource* data_source, OpFlipX op) {
    do_flip_x(data_source, op);
}
