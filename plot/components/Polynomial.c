#include "Polynomial.h"

#include <math.h>
#include <stdlib.h>

#include "../../math/regression.h"

#define POINT_COUNT 100

Vector2* points = NULL;
int point_count = 0;

void gen_points(CurvePolynomial* curve, const float start_x, const int count) {
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
        curve->point_buffer[i] = transform_v_to_pixel((Vector2) {x + curve->normal_offset_x, y}, bounds);
    }
}

void Polynomial(CurvePolynomial* curve, Vector2* points, const int point_count, move_change_t change, const Bounds bounds) {
    if (curve->point_buffer == NULL) {
        curve->point_buffer = malloc(POINT_COUNT * sizeof curve->point_buffer[0]);
        change |= MOVE_CHANGE_POLYNOMIAL;
    }

    if (!point_count) {
        gen_points(curve, -5, 29);
        change |= MOVE_CHANGE_POLYNOMIAL;
    }

    if (change & MOVE_CHANGE_POLYNOMIAL) {
        regression(curve, points, point_count, 4);
    }
    if (change) {
        DrawRectangle(0, PLOT_HEIGHT - 7, 7, 7, RED);
        compute_points(curve, bounds);
    }

    DrawSplineLinear(curve->point_buffer, POINT_COUNT, 4, RED);

    for (int i = 0; i < point_count; ++i) {
        const Vector2 p = { points[i].x + curve->normal_offset_x, points[i].y };
        DrawCircleV(transform_v_to_pixel(p, bounds), 2, ORANGE);
    }
}
