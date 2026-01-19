#ifndef SPECZANIE_DO_CUT_LEFT_H
#define SPECZANIE_DO_CUT_LEFT_H

#include "../data_source.h"

typedef struct {
    int index;
} OpCutLeft;

OpCutLeft do_cut_left(DataSource* data_source, OpCutLeft op);
void undo_cut_left(DataSource* data_source, OpCutLeft op);

#endif //SPECZANIE_DO_CUT_LEFT_H