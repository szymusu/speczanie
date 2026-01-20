#include "input_mode.h"

enum InputMode input_mode = INPUT_MODE_IDLE;

bool is_input_mode(const enum InputMode _input_mode) {
    return input_mode == _input_mode;
}
void set_input_mode(const enum InputMode _input_mode) {
    input_mode = _input_mode;
}
enum InputMode get_input_mode() {
    return input_mode;
}
