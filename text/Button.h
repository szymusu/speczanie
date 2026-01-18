#ifndef BUTTON_H
#define BUTTON_H

#include "TextBox.h"

#define BUTTON_STATE_IDLE 0
#define BUTTON_STATE_CLICKED 1
#define BUTTON_STATE_HOVER 2
typedef unsigned char button_state_t;

#define BUTTON_OPTION_ACTIVE 1
#define BUTTON_OPTION_DISABLED 2
typedef unsigned char button_options_t;

button_state_t ButtonPro(TextBoxProps idle_props, TextBoxProps hover_props);
button_state_t Button(Vector2 origin, const char* text, float font_size, textbox_align_t align);
button_state_t ButtonDefault(Vector2 origin, const char* text, float font_size, button_options_t options);

#endif //BUTTON_H
