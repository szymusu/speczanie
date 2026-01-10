# Algorytm regresji wielomianowej

## pierwotna funkcja
```c++
void regression(CurvePolynomial* curve, const Vector2* points, const int point_count) {
    clock_start();
    const int degree = point_count - 1;
    const int n = point_count;
    const int m = degree;

    float* matrix = malloc((m*m + 2*m) * sizeof (float)  +  m * sizeof (int));
    float* errors = &matrix[m*m];
    float* coeffs = &errors[m];
    int* swap_table = (int*) &coeffs[m];

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
```

### debug
```
samples: 10000
cycles: 1228592 avg 1182240 best
ms: 0.340353 avg 0.328000 best
samples: 10000
cycles: 1222491 avg 1187676 best
ms: 0.338560 avg 0.329000 best
samples: 10000
cycles: 1221949 avg 1184508 best
ms: 0.338329 avg 0.328000 best
samples: 10000
cycles: 1219704 avg 1187136 best
ms: 0.337932 avg 0.328000 best
```


### release
```
samples: 10000
cycles: 951561 avg 913932 best
ms: 0.263545 avg 0.253000 best
samples: 10000
cycles: 952509 avg 913644 best
ms: 0.263831 avg 0.253000 best
samples: 10000
cycles: 939618 avg 913608 best
ms: 0.260251 avg 0.252000 best
samples: 10000
cycles: 942651 avg 914544 best
ms: 0.261089 avg 0.253000 best
```


## 