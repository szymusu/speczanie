#include "op_flip_y.h"

OpFlipY do_flip_y(DataSource* data_source, OpFlipY op) {
    for (int i = 0; i < data_source->count; ++i) {
        data_source->data[i].y *= -1;
    }
    return op;
}

void undo_flip_y(DataSource* data_source, OpFlipY op) {
    do_flip_y(data_source, op);
}