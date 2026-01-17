#include "Axes.h"

#include <raylib.h>

#include "../plot_math.h"
#include "../../text/text.h"

#define LINE_LEN 80
#define PADDING 30
#define ARROW 10

void Axes(const char* x_label, const char* y_label) {
    DrawLineEx(
        (Vector2) {PLOT_OFFSET_X + PADDING, PLOT_HEIGHT - PADDING},
        (Vector2) {PLOT_OFFSET_X + PADDING + LINE_LEN, PLOT_HEIGHT - PADDING},
        3, BLACK
        );
    DrawLineEx(
        (Vector2) {PLOT_OFFSET_X + PADDING + LINE_LEN, PLOT_HEIGHT - PADDING},
        (Vector2) {PLOT_OFFSET_X + PADDING + LINE_LEN - ARROW, PLOT_HEIGHT - PADDING + ARROW},
        3, BLACK
    );
    DrawLineEx(
        (Vector2) {PLOT_OFFSET_X + PADDING + LINE_LEN, PLOT_HEIGHT - PADDING},
        (Vector2) {PLOT_OFFSET_X + PADDING + LINE_LEN - ARROW, PLOT_HEIGHT - PADDING - ARROW},
        3, BLACK
    );
    Text(x_label, PLOT_OFFSET_X + PADDING + LINE_LEN + ARROW, PLOT_HEIGHT - PADDING - 7, 16, BLACK);


    DrawLineEx(
        (Vector2) {PLOT_OFFSET_X + PADDING, PLOT_HEIGHT - PADDING},
        (Vector2) {PLOT_OFFSET_X + PADDING, PLOT_HEIGHT - PADDING - LINE_LEN},
        3, BLACK
        );
    DrawLineEx(
        (Vector2) {PLOT_OFFSET_X + PADDING, PLOT_HEIGHT - PADDING - LINE_LEN},
        (Vector2) {PLOT_OFFSET_X + PADDING - ARROW, PLOT_HEIGHT - PADDING - LINE_LEN + ARROW},
        3, BLACK
        );
    DrawLineEx(
        (Vector2) {PLOT_OFFSET_X + PADDING, PLOT_HEIGHT - PADDING - LINE_LEN},
        (Vector2) {PLOT_OFFSET_X + PADDING + ARROW, PLOT_HEIGHT - PADDING - LINE_LEN + ARROW},
        3, BLACK
        );
    Text(y_label, PLOT_OFFSET_X + ARROW, PLOT_HEIGHT - PADDING - LINE_LEN - PADDING + ARROW, 16, BLACK);
}
