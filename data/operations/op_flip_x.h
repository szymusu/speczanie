#ifndef SPECZANIE_OP_FLIP_X_H
#define SPECZANIE_OP_FLIP_X_H

#include "../data_source.h"

typedef struct {} OpFlipX;

OpFlipX do_flip_x(DataSource* data_source, OpFlipX op);
void undo_flip_x(DataSource* data_source, OpFlipX op);

#endif //SPECZANIE_OP_FLIP_X_H