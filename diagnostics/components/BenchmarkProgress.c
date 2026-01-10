#include "BenchmarkProgress.h"

#include <raylib.h>

#include "Clock.h"
#include "../../text/Button.h"

#define LEFT 300
#define TOP 30
#define WIDTH 600
#define HEIGHT 20

void BenchmarkProgress(const int current, const int max) {
    if (current == -1) {
        const button_state_t button = Button((Vector2) {LEFT, TOP}, "Start benchmark", 16, 0);
        if (button == BUTTON_STATE_CLICKED) {
            benchmark_start();
        }
        return;
    }

    const float progress = (float) current / (float) max;
    const int width = progress * WIDTH;

    DrawRectangle(LEFT, TOP, width, HEIGHT, GREEN);
    DrawRectangleLines(LEFT, TOP, WIDTH, HEIGHT, BLACK);
}
