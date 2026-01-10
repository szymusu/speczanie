#include "regression.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "vector2.h"

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

void swap_rows(int* swap_table, const int row1, const int row2) {
    const int tmp = swap_table[row1];
    swap_table[row1] = swap_table[row2];
    swap_table[row2] = tmp;
}

void regression(CurvePolynomial* curve, const Vector2* points, const int point_count) {
    const int degree = point_count - 1;
    const int n = point_count;
    const int m = degree;

    float* matrix = malloc(m * m * sizeof (float));
    float* errors = malloc(m * sizeof (float));
    float* coeffs = malloc(m * sizeof (float));
    int* swap_table = malloc(m * sizeof (int));

    for (int row = 0; row < m; ++row) {
        swap_table[row] = row;

        for (int col = 0; col < m; ++col) {
            float cell = 0;
            const int power = row + col;
            for (int i = 0; i < n; ++i) {
                cell += pownf(points[i].x, power);
            }
            _get_mat_cell(row, col) = cell;
        }
        float error = 0;
        for (int i = 0; i < n; ++i) {
            error += pownf(points[i].x, row) * points[i].y;
        }
        _get_error(row) = error;
    }

    // e_matrix_print(matrix, errors, swap_table, m);

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
    // e_matrix_print(matrix, errors, swap_table, m);

    _get_coeff(m - 1) = _get_error(m - 1) / _get_mat_cell(m - 1, m - 1);
    for (int i = m - 2; i >= 0; --i) {
        float sigma = 0;
        for (int k = i + 1; k < m; ++k) {
            sigma += _get_mat_cell(i, k) * _get_coeff(k);
        }
        _get_coeff(i) = (_get_error(i) - sigma) / _get_mat_cell(i, i);
    }

    // for (int i = 0; i < m; ++i) {
    //     printf("%.2f  ", coeffs[i]);
    // }
    // putchar('\n');



    for (int i = 0; i < m; ++i) {
        curve->coefficients[i] = _get_coeff(i);
    }
    free(matrix);
    free(errors);
    free(coeffs);
    free(swap_table);

    curve->order = m;
    curve->start_x = points[0].x;
    curve->end_x = points[point_count - 1].x;
}
