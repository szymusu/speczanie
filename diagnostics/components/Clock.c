#include "Clock.h"

#ifdef _WIN32
#include <intrin.h>
#endif
#ifndef __arm64
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
#ifndef __arm64
    start_cycles = __rdtsc();
#endif
    start = clock();
}

void clock_end() {
#ifndef __arm64
    end_cycles = __rdtsc();
#endif
    end = clock();
    sprintf(clock_text, "Cycles: %ld\nms: %lf", end_cycles - start_cycles, (end - start) * 1000. / CLOCKS_PER_SEC);
}

void Clock() {
    Text(clock_text, 0, 410, 20, BLACK);
}
