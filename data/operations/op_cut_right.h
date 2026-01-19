#ifndef SPECZANIE_OP_CUT_RIGHT_H
#define SPECZANIE_OP_CUT_RIGHT_H

#include "../data_source.h"

typedef struct {
    int index;
} OpCutRight;

OpCutRight do_cut_right(DataSource* data_source, OpCutRight op);
void undo_cut_right(DataSource* data_source, OpCutRight op);

#endif //SPECZANIE_OP_CUT_RIGHT_H