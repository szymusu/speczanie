#include "regression.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "vector2.h"
#include "../diagnostics/components/Clock.h"

#define _get_mat_cell(row, col) matrix[swap_table[row] * m + col]
#define _get_error(row) errors[swap_table[row]]
#define _get_coeff(row) coeffs[swap_table[row]]

void e_matrix_print(const float* matrix, const float* errors, const int* swap_table, const int m) {
    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < m; ++col) {
            printf("  %2.2f  ", _get_mat_cell(row, col));
        }
        printf("|  %2.2f  ", _get_error(row));
        putchar('\n');
    }
    putchar('\n');
}

float normalize(Vector2* points, const int count) {
    const float offset = points[0].x;
    for (int i = 0; i < count; ++i) {
        points[i].x -= offset;
    }
    return offset;
}

void swap_rows(int* swap_table, const int row1, const int row2) {
    const int tmp = swap_table[row1];
    swap_table[row1] = swap_table[row2];
    swap_table[row2] = tmp;
}

void regression(CurvePolynomial* curve, Vector2* points, const int point_count, const int degree) {
    curve->normal_offset_x = normalize(points, point_count);
    clock_start();
    // printf("%f\n", power_fi(2, 3));
    const int n = point_count;
    const int m = degree;

    float* matrix = malloc((m*m + 4*m + 3*n) * sizeof (float)  +  m * sizeof (int));
    float* errors = &matrix[m*m];
    float* coeffs = &errors[m];
    float* sum_of_powers = &coeffs[m];
    float* points_x = &sum_of_powers[2 * m];
    float* points_x_powers = &points_x[n];
    float* points_x_powers_y = &points_x_powers[n];
    int* swap_table = (int*) &points_x_powers_y[n];

    sum_of_powers[0] = (float) n;
    sum_of_powers[1] = 0;
    for (int i = 0; i < n; ++i) {
        const float x = points[i].x;
        points_x[i] = x;
        points_x_powers[i] = x;
        sum_of_powers[1] += x;
    }
    for (int pow = 2; pow < 2 * m; ++pow) {
        float total = 0;
        for (int i = 0; i < n; ++i) {
            points_x_powers[i] *= points_x[i];
            total += points_x_powers[i];
        }
        sum_of_powers[pow] = total;
    }

    for (int row = 0; row < m; ++row) {
        swap_table[row] = row;

        for (int col = 0; col < m; ++col) {
            matrix[row * m + col] = sum_of_powers[row + col];
        }
    }

    errors[0] = 0;
    for (int i = 0; i < n; ++i) {
        const float y = points[i].y;
        points_x_powers_y[i] = y;
        errors[0] += y;
    }
    for (int pow = 1; pow < m; ++pow) {
        float total = 0;
        for (int i = 0; i < n; ++i) {
            points_x_powers_y[i] *= points_x[i];
            total += points_x_powers_y[i];
        }
        errors[pow] = total;
    }

    for (int i = 0; i < m - 1; ++i) {
        float max = fabsf(_get_mat_cell(i, i));
        int max_row = i;
        for (int row = i + 1; row < m; ++row) {
            const float current_abs = fabsf(_get_mat_cell(row, i));
            if (current_abs > max) {
                max = current_abs;
                max_row = row;
            }
        }
        if (max_row != i) swap_rows(swap_table, i, max_row);

        const float cell = _get_mat_cell(i, i);
        for (int row = i + 1; row < m; ++row) {
            const float coeff = _get_mat_cell(row, i) / cell;
            _get_error(row) -= coeff * _get_error(i);
            for (int col = 0; col < m; ++col) {
                _get_mat_cell(row, col) -= coeff * _get_mat_cell(i, col);
            }
        }
    }

    _get_coeff(m - 1) = _get_error(m - 1) / _get_mat_cell(m - 1, m - 1);
    for (int i = m - 2; i >= 0; --i) {
        float sigma = 0;
        for (int k = i + 1; k < m; ++k) {
            sigma += _get_mat_cell(i, k) * _get_coeff(k);
        }
        _get_coeff(i) = (_get_error(i) - sigma) / _get_mat_cell(i, i);
    }

    for (int i = 0; i < m; ++i) {
        curve->coefficients[i] = _get_coeff(i);
    }
    free(matrix);

    curve->order = m;
    curve->start_x = points[0].x;
    curve->end_x = points[point_count - 1].x;
    clock_end();
}
