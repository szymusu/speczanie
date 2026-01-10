#include "Polynomial.h"

#include <stdlib.h>

#include "../../math/regression.h"

#define POINT_COUNT 100

const Vector2 points[] = {
    {-3, 3},
    {-2, 2.7f},
    {-1, 2.2f},
    {0, 1.5f},
    {1, .5f},

    // {.1f, .1f},
    // {.35f, .45f},
    // {.6f, .8f},
};
const int point_count = sizeof points / sizeof points[0];

float f(const float x, const float* coefficients, const uint8_t order) {
    float y = 0;
    float x_multiplied = 1;
    for (uint8_t i = 0; i < order; ++i) {
        y += x_multiplied * coefficients[i];
        x_multiplied *= x;
    }
    return y;
}

void compute_points(CurvePolynomial curve, const Bounds bounds) {
    const float step = (curve.end_x - curve.start_x) / POINT_COUNT;
    float x = curve.start_x;
    for (int i = 0; i < POINT_COUNT; ++i) {
        x += step;
        const float y = f(x, curve.coefficients, curve.order);
        curve.point_buffer[i] = transform_v_to_pixel((Vector2) {x, y}, bounds);
    }
}

void Polynomial(CurvePolynomial curve, move_change_t change, const Bounds bounds) {
    if (!curve.order) {
        if (curve.point_buffer) free(curve.point_buffer);
        return;
    }
    if (!curve.point_buffer) {
        curve.point_buffer = malloc(POINT_COUNT * sizeof curve.point_buffer[0]);
        change |= MOVE_CHANGE_POLYNOMIAL;
    }

    regression(&curve, points, point_count);
    if (change) {
        compute_points(curve, bounds);
    }

    DrawSplineLinear(curve.point_buffer, POINT_COUNT, 2.f, LIGHTGRAY);

    for (int i = 0; i < point_count; ++i) {
        DrawCircleV(transform_v_to_pixel(points[i], bounds), 2, BLACK);
    }
}