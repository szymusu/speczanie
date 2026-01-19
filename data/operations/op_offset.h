#ifndef SPECZANIE_OP_OFFSET_H
#define SPECZANIE_OP_OFFSET_H

#include "../data_source.h"

typedef struct {
    Vector2 offset;
} OpOffset;

OpOffset do_offset(DataSource* data_source, OpOffset op);
void undo_offset(DataSource* data_source, OpOffset op);

#endif //SPECZANIE_OP_OFFSET_H