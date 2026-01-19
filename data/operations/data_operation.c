#include "data_operation.h"

#include <stdio.h>
#include <stdlib.h>

#define START_CAPACITY 1
#define OPERATION_SIZE (sizeof (DataOperation))

DataOperationStack data_operation_stack_init() {
    return (DataOperationStack) {
        .operations = malloc(OPERATION_SIZE * START_CAPACITY),
        .count = 0,
        .capacity = START_CAPACITY
    };
}

void data_operation_stack_free(DataOperationStack* stack) {
    free(stack->operations);
}

void data_operation_push(DataOperationStack* stack, const DataOperation operation) {
    stack->count++;
    if (stack->count == stack->capacity) {
        printf("Resizing %d -> ", stack->capacity);
        stack->capacity *= 2;
        printf("%d\n", stack->capacity);
        DataOperation* new_buffer = realloc(stack->operations, stack->capacity * OPERATION_SIZE);
        if (!new_buffer) return;
        stack->operations = new_buffer;
    }
    stack->operations[stack->count - 1] = operation;
}

DataOperation data_operation_pop(DataOperationStack* stack) {
    if (stack->count == 0) return (DataOperation) { .type = OP_NONE };

    return stack->operations[--stack->count];
}

void data_operation_do(DataSource* data_source, DataOperationStack* stack, DataOperation operation) {
    switch (operation.type) {
    case OP_NONE:
        break;
    case OP_CUT_LEFT:
        operation.op.cut_left = do_cut_left(data_source, operation.op.cut_left);
        break;
    case OP_CUT_RIGHT:
        operation.op.cut_right = do_cut_right(data_source, operation.op.cut_right);
        break;
    case OP_FLIP_Y:
        operation.op.flip_y = do_flip_y(data_source, operation.op.flip_y);
        break;
    }

    data_operation_push(stack, operation);
}

void data_operation_undo(DataSource* data_source, DataOperationStack* stack) {
    const DataOperation operation = data_operation_pop(stack);

    switch (operation.type) {
    case OP_NONE:
        puts("Undo empty");
        break;
    case OP_CUT_LEFT:
        printf("Undo cut left %d\n", operation.op.cut_left.index);
        undo_cut_left(data_source, operation.op.cut_left);
        break;
    case OP_CUT_RIGHT:
        printf("Undo cut right %d\n", operation.op.cut_left.index);
        undo_cut_right(data_source, operation.op.cut_right);
        break;
    case OP_FLIP_Y:
        printf("Undo flip Y\n");
        undo_flip_y(data_source, operation.op.flip_y);
        break;
    }
}
