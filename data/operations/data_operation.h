#ifndef SPECZANIE_DATA_OPERATION_H
#define SPECZANIE_DATA_OPERATION_H

#include "op_cut_left.h"

enum DataOperationType {
    OP_NONE,
    OP_CUT_LEFT,
};

typedef struct  {
    union {
        OpCutLeft cut_left;
    } op;

    enum DataOperationType type;
} DataOperation;

typedef struct {
    DataOperation* operations;
    int count;
    int capacity;

} DataOperationStack;

DataOperationStack data_operation_stack_init();
void data_operation_stack_free(DataOperationStack* stack);
void data_operation_do(DataSource* data_source, DataOperationStack* stack, DataOperation operation);
void data_operation_undo(DataSource* data_source, DataOperationStack* stack);

#endif //SPECZANIE_DATA_OPERATION_H