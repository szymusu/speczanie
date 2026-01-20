#ifndef SPECZANIE_INPUT_MODE_H
#define SPECZANIE_INPUT_MODE_H

#include <stdbool.h>

enum InputMode {
    INPUT_MODE_IDLE,
    INPUT_MODE_MOVE,
    INPUT_MODE_SELECT,
    INPUT_MODE_REGRESSION,
    INPUT_MODE_TEXT,
};

bool is_input_mode(enum InputMode _input_mode);
void set_input_mode(enum InputMode _input_mode);
enum InputMode get_input_mode();

#endif //SPECZANIE_INPUT_MODE_H