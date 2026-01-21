#ifndef SPECZANIE_TEXTINPUT_H
#define SPECZANIE_TEXTINPUT_H

#define TEXT_CHANGE_NONE 0
#define TEXT_CHANGE_INPUT 1
#define TEXT_CHANGE_UNFOCUS 2
#define TEXT_CHANGE_FOCUS 4
#define TEXT_CHANGE_ENTER 8

#include <stdbool.h>

typedef unsigned char text_change_t;

text_change_t TextInput(float x, float y, char* buffer, int* len, int max_len, bool is_focused);

#endif //SPECZANIE_TEXTINPUT_H