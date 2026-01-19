#ifndef SPECZANIE_OP_FLIP_Y_H
#define SPECZANIE_OP_FLIP_Y_H

#include "../data_source.h"

typedef struct {} OpFlipY;

OpFlipY do_flip_y(DataSource* data_source, OpFlipY op);
void undo_flip_y(DataSource* data_source, OpFlipY op);

#endif //SPECZANIE_OP_FLIP_Y_H