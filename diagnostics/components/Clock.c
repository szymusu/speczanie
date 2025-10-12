#include "Clock.h"

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "../../text/text.h"

char clock_text[64];
clock_t start = 0, end = 0;
unsigned long long start_cycles = 0, end_cycles = 0;

void clock_start() {
    start_cycles = __rdtsc();
    start = clock();
}

void clock_end() {
    end_cycles = __rdtsc();
    end = clock();
    sprintf(clock_text, "Cycles: %ld\nms: %lf", end_cycles - start_cycles, (end - start) * 1000. / CLOCKS_PER_SEC);
}

void Clock() {
    Text(clock_text, 0, 410, 20, BLACK);
}
