#include "op_offset.h"

OpOffset do_offset(DataSource* data_source, OpOffset op) {
    for (int i = 0; i < data_source->count; ++i) {
        data_source->data[i].x += op.offset.x;
        data_source->data[i].y -= op.offset.y;
    }
    return op;
}

void undo_offset(DataSource* data_source, OpOffset op) {
    op.offset.x *= -1;
    op.offset.y *= -1;
    do_offset(data_source, op);
}
