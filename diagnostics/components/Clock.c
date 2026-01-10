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

#include "../../plot/plot_math.h"
#include "../../text/text.h"

char clock_text[64];
clock_t start = 0, end = 0;
unsigned long long start_cycles = 0, end_cycles = 0;

clock_t sum = 0, best = -1;
unsigned long long sum_cycles = 0, best_cycles = -1;
int samples = -1;


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
    const clock_t diff = end - start;
    const unsigned long long diff_cycles = end_cycles - start_cycles;
    sprintf(clock_text, "Cycles: %llu\nms: %lf", diff_cycles, diff * 1000. / CLOCKS_PER_SEC);

    if (samples == -1) return;
    if (samples < CLOCK_SAMPLE_COUNT) {
        samples++;
        sum += diff;
        sum_cycles += diff_cycles;
        if (best == -1 || diff < best) best = diff;
        if (best_cycles == -1 || diff_cycles < best_cycles) best_cycles = diff_cycles;

        if (samples == CLOCK_SAMPLE_COUNT) {
            printf("samples: %d\ncycles: %llu avg %llu best\nms: %lf avg %lf best\n",
                CLOCK_SAMPLE_COUNT,
                sum_cycles / CLOCK_SAMPLE_COUNT,
                best_cycles,
                sum  * 1000. / CLOCK_SAMPLE_COUNT / CLOCKS_PER_SEC,
                best * 1000. / CLOCKS_PER_SEC
                );
            samples = -1;
            sum = 0;
            sum_cycles = 0;
            best = -1;
            best_cycles = -1;
        }
    }
}

void Clock() {
    Text(clock_text, 0, PLOT_HEIGHT - 40, 20, BLACK);
}

int get_sample_count() {
    return samples;
}

void benchmark_start() {
    samples = 0;
}
