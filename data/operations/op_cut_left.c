#include "op_cut_left.h"

void do_cut_left(DataSource* data_source, OpCutLeft op) {
    data_source->count -= op.index;
    data_source->data += op.index;
}

void undo_cut_left(DataSource* data_source, OpCutLeft op) {
    data_source->data -= op.index;
    data_source->count += op.index;
}
