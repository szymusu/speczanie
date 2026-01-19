#ifndef SPECZANIE_OP_REPLACE_H
#define SPECZANIE_OP_REPLACE_H

#include "../data_source.h"

typedef struct {
    Vector2 point;
    int index;
} OpReplace;

OpReplace do_replace(DataSource* data_source, OpReplace op);
void undo_replace(DataSource* data_source, OpReplace op);

#endif //SPECZANIE_OP_REPLACE_H