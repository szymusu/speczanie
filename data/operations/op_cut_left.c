#include "op_cut_left.h"

OpCutLeft do_cut_left(DataSource* data_source, const OpCutLeft op) {
    data_source->count -= op.index;
    data_source->data += op.index;
    return op;
}

void undo_cut_left(DataSource* data_source, const OpCutLeft op) {
    data_source->data -= op.index;
    data_source->count += op.index;
}
