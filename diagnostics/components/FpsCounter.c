#include "FpsCounter.h"

#include <raylib.h>
#include <stdio.h>
#include <stdint.h>

#include "../../text/text.h"

#define COUNT 4096

void FpsCounter() {
    static char text[64] = {0};
    static int buffer[COUNT] = {0};
    static int sum = 0;
    static int index = 0;
    static float max_time = 0;

    const int current = GetFPS();

    const int old = buffer[index];
    sum = sum - old + current;
    buffer[index] = current;

    if (++index == COUNT) index = 0;

    const float time = GetFrameTime();
    if (time > max_time) max_time = time;

    DrawRectangle(0, 0, 65, (15-3)*3+10, RAYWHITE);

    sprintf(text, "FPS %d\navg %d\nmax %.4f ms", current, sum / COUNT, max_time);
    SetTextLineSpacing(-3);
    Text(text, 5, 5, 15, BLACK);
    SetTextLineSpacing(0);
}
