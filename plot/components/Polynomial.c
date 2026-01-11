#include "Polynomial.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../diagnostics/components/Clock.h"
#include "../../math/regression.h"

#define POINT_COUNT 100

Vector2* points = nullptr;
int point_count = 0;

void gen_points(CurvePolynomial* curve, const float start_x, const int count) {
    // curve->coefficients = malloc(3 * sizeof *curve->coefficients);
    // point_count = 3;
    // points = malloc(3 * sizeof *points);
    // points[0] = (Vector2) {.1f, .1f};
    // points[1] = (Vector2) {.35f, .45f};
    // points[2] = (Vector2) {.6f, .8f};

    curve->coefficients = malloc(count * sizeof *curve->coefficients);

    points = malloc(count * sizeof *points);
    point_count = count;
    float x = start_x;
    for (int i = 0; i < count; ++i, x += .3f) {
        points[i].x = x;
        points[i].y = sinf(x) * 2 + 2;
    }
}

float f(const float x, const float* coefficients, const uint8_t order) {
    float y = 0;
    float x_multiplied = 1;
    for (uint8_t i = 0; i < order; ++i) {
        y += x_multiplied * coefficients[i];
        x_multiplied *= x;
    }
    return y;
}

void compute_points(CurvePolynomial* curve, const Bounds bounds) {
    const float step = (curve->end_x - curve->start_x) / POINT_COUNT;
    float x = curve->start_x;
    for (int i = 0; i < POINT_COUNT; ++i) {
        x += step;
        const float y = f(x, curve->coefficients, curve->order);
        curve->point_buffer[i] = transform_v_to_pixel((Vector2) {x, y}, bounds);
    }
}

void Polynomial(CurvePolynomial* curve, move_change_t change, const Bounds bounds) {
    // if (!curve->order) {
    //     if (curve->point_buffer) free(curve->point_buffer);
    //     return;
    // }
    if (curve->point_buffer == NULL) {
        curve->point_buffer = malloc(POINT_COUNT * sizeof curve->point_buffer[0]);
        change |= MOVE_CHANGE_POLYNOMIAL;
    }
    if (change) {
        DrawRectangle(50, 0, 20, 50, RED);
    }
    if (!point_count) {
        gen_points(curve, -5, 29);
        change |= MOVE_CHANGE_POLYNOMIAL;
    }

    if (change) {
        regression(curve, points, point_count);

        compute_points(curve, bounds);
        // for (int i = 0; i < curve->order; ++i) {
        //     printf("%.2f  ", curve->coefficients[i]);
        // }
        // putchar('\n');
    }
    Clock();

    DrawSplineLinear(curve->point_buffer, POINT_COUNT, 2.f, LIGHTGRAY);

    for (int i = 0; i < point_count; ++i) {
        DrawCircleV(transform_v_to_pixel(points[i], bounds), 2, BLACK);
    }
}