#include "op_cut_right.h"

OpCutRight do_cut_right(DataSource* data_source, OpCutRight op) {
    const int prev = data_source->count;
    data_source->count = op.index + 1;
    op.index = prev;
    return op;
}

void undo_cut_right(DataSource* data_source, OpCutRight op) {
    data_source->count = op.index;
}