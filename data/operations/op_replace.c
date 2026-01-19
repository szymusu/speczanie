#include "op_replace.h"

OpReplace do_replace(DataSource* data_source, OpReplace op) {
    const Vector2 prev = data_source->data[op.index];
    data_source->data[op.index] = op.point;
    op.point = prev;
    return op;
}

void undo_replace(DataSource* data_source, OpReplace op) {
    data_source->data[op.index] = op.point;
}
