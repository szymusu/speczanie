#include "FpsCounter.h"

#include <raylib.h>
#include <stdio.h>
#include <stdint.h>

void FpsCounter() {
    static char text[64] = {0};
    static int min = 999999;
    static int buffer[256] = {0};
    static int sum = 0;
    static uint8_t index = 0;

    const int current = GetFPS();
    if (current < min) min = current;

    const int old = buffer[index];
    sum = sum - old + current;
    buffer[index] = current;

    ++index;

    sprintf(text, "FPS %d\nmin %d\navg %d", current, min, sum / 256);
    DrawText(text, 10, 10, 13, BLACK);
}
