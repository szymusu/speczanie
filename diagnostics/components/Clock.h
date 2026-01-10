#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_SAMPLE_COUNT (10000)

void Clock();
void clock_start();
void clock_end();
int get_sample_count();
void benchmark_start();

#endif //CLOCK_H
