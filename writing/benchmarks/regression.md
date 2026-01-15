# Algorytm regresji wielomianowej

## dane wejściowe
29 punktów na krzywej 2sinx + 2
od -5, co 0.3

## pierwotna funkcja
```c++
void regression(CurvePolynomial* curve, const Vector2* points, const int point_count) {
    clock_start();
    // przygotowanie
    const int degree = point_count - 1;
    const int n = point_count;
    const int m = degree;

    float* matrix = malloc((m*m + 2*m) * sizeof (float)  +  m * sizeof (int));
    float* errors = &matrix[m*m];
    float* coeffs = &errors[m];
    int* swap_table = (int*) &coeffs[m];

    // wypełananie macierzy i wektora
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

    // eliminacja Gaussa - postępowanie proste
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

    // eliminacja Gaussa - postępowanie odweotne
    _get_coeff(m - 1) = _get_error(m - 1) / _get_mat_cell(m - 1, m - 1);
    for (int i = m - 2; i >= 0; --i) {
        float sigma = 0;
        for (int k = i + 1; k < m; ++k) {
            sigma += _get_mat_cell(i, k) * _get_coeff(k);
        }
        _get_coeff(i) = (_get_error(i) - sigma) / _get_mat_cell(i, i);
    }

    // przepisanie wyników i zwolnienie pamięci
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

## overhead benchmarku
```c++
clock_start();
clock_end();
```
### debug
```
samples: 10000
cycles: 3642 avg 2592 best
ms: 0.000814 avg 0.000000 best
samples: 10000
cycles: 3561 avg 2484 best
ms: 0.000791 avg 0.000000 best
samples: 10000
cycles: 3604 avg 2520 best
ms: 0.000800 avg 0.000000 best
samples: 10000
cycles: 3683 avg 2592 best
ms: 0.000810 avg 0.000000 best
```
### release
```
samples: 10000
cycles: 3880 avg 2628 best
ms: 0.000817 avg 0.000000 best
samples: 10000
cycles: 3615 avg 2556 best
ms: 0.000789 avg 0.000000 best
samples: 10000
cycles: 3713 avg 2736 best
ms: 0.000796 avg 0.000000 best
samples: 10000
cycles: 3569 avg 2700 best
ms: 0.000775 avg 0.000000 best
```

## alokacja pamięci i ustawienie wskaźników
```c++
clock_start();
const int degree = point_count - 1;
const int n = point_count;
const int m = degree;

float* matrix = malloc((m*m + 2*m) * sizeof (float)  +  m * sizeof (int));
float* errors = &matrix[m*m];
float* coeffs = &errors[m];
int* swap_table = (int*) &coeffs[m];
clock_end();
```
### debug
```
samples: 10000
cycles: 4331 avg 2952 best
ms: 0.000950 avg 0.000000 best
```
### release
```
samples: 10000
cycles: 4131 avg 3168 best
ms: 0.000930 avg 0.000000 best
```

## wypełnianie macierzy i wektora błędów
```c++
clock_start();
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
clock_end();
```

### debug
```
samples: 10000
cycles: 1064016 avg 1010808 best
ms: 0.294737 avg 0.281000 best
samples: 10000
cycles: 1045250 avg 1008720 best
ms: 0.289477 avg 0.280000 best
samples: 10000
cycles: 1049505 avg 1009584 best
ms: 0.290731 avg 0.280000 best
samples: 10000
cycles: 1056144 avg 1012932 best
ms: 0.292435 avg 0.281000 best
```

### release
```
samples: 10000
cycles: 938385 avg 898308 best
ms: 0.259947 avg 0.248000 best
samples: 10000
cycles: 927664 avg 898488 best
ms: 0.256944 avg 0.248000 best
samples: 10000
cycles: 922574 avg 898020 best
ms: 0.255469 avg 0.248000 best
samples: 10000
cycles: 930611 avg 898092 best
ms: 0.257770 avg 0.248000 best
```

## rozwiązanie układu równań
```c++
clock_start();
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
clock_end();
```
### debug
```
samples: 10000
cycles: 187736 avg 180720 best
ms: 0.051796 avg 0.047000 best
samples: 10000
cycles: 184986 avg 180684 best
ms: 0.051078 avg 0.048000 best
samples: 10000
cycles: 185314 avg 180900 best
ms: 0.051125 avg 0.048000 best
samples: 10000
cycles: 186258 avg 180792 best
ms: 0.051409 avg 0.049000 best
```
### release
```
samples: 10000
cycles: 13700 avg 12240 best
ms: 0.003580 avg 0.000000 best
samples: 10000
cycles: 13416 avg 12204 best
ms: 0.003531 avg 0.003000 best
samples: 10000
cycles: 13402 avg 12348 best
ms: 0.003536 avg 0.001000 best
samples: 10000
cycles: 13398 avg 12240 best
ms: 0.003525 avg 0.000000 best
```
### kompilator robi robotę
Na release (-O3) jest 10 razy szybciej :o

## przepisywanie wyniku i zwalnianie pamięci
```c++
clock_start();
for (int i = 0; i < m; ++i) {
    curve->coefficients[i] = _get_coeff(i);
}
free(matrix);

curve->order = m;
curve->start_x = points[0].x;
curve->end_x = points[point_count - 1].x;
clock_end();
```
### debug
```
samples: 10000
cycles: 3960 avg 3132 best
ms: 0.000895 avg 0.000000 best
samples: 10000
cycles: 3953 avg 3132 best
ms: 0.000887 avg 0.000000 best
samples: 10000
cycles: 3925 avg 3132 best
ms: 0.000885 avg 0.000000 best
samples: 10000
cycles: 4049 avg 3168 best
ms: 0.000900 avg 0.000000 best
```
### release
```
samples: 10000
cycles: 3809 avg 3168 best
ms: 0.000859 avg 0.000000 best
samples: 10000
cycles: 3921 avg 2844 best
ms: 0.000870 avg 0.000000 best
samples: 10000
cycles: 3844 avg 3096 best
ms: 0.000854 avg 0.000000 best
samples: 10000
cycles: 3712 avg 2880 best
ms: 0.000842 avg 0.000000 best
```

## mamy hot spot
Zdecydowana większość czasu spędzana jest na wypełnianiu macierzy i wektora sumami.


## zmiana funkcji potęgi
```c++
clock_start();
for (int row = 0; row < m; ++row) {
    swap_table[row] = row;

    for (int col = 0; col < m; ++col) {
        float cell = 0;
        const int power = row + col;
        for (int i = 0; i < n; ++i) {
            cell += power_fi(points[i].x, power);
        }
        matrix[row * m + col] = cell;
    }
    float error = 0;
    for (int i = 0; i < n; ++i) {
        error += power_fi(points[i].x, row) * points[i].y;
    }
    errors[row] = error;
}
clock_end();
```
```c++
float power_fi(const float x, int pow) {
    if (pow == 0) return 1;
    float res = x;
    while (--pow) {
        res *= x;
    }
    return res;
}
```

### debug
```
samples: 10000
cycles: 4380990 avg 4185072 best
ms: 1.214246 avg 1.163000 best
```
### release
```
samples: 10000
cycles: 671631 avg 646632 best
ms: 0.185943 avg 0.179000 best
samples: 10000
cycles: 672397 avg 644472 best
ms: 0.186236 avg 0.175000 best
samples: 10000
cycles: 675776 avg 648216 best
ms: 0.187136 avg 0.179000 best
samples: 10000
cycles: 670312 avg 647784 best
ms: 0.185646 avg 0.179000 best
```

### compiler magic
Bez optymalizacji jest 4 razy wolniej, z optymalizacją 25% szybciej, beka


## cacheowanie sum potęg x

```c++
clock_start();
for (int pow = 0; pow < 2*m; ++pow) {
    float total = 0;
    for (int i = 0; i < n; ++i) {
        total += pownf(points[i].x, pow);
    }
    powers[pow] = total;
}

for (int row = 0; row < m; ++row) {
    swap_table[row] = row;

    for (int col = 0; col < m; ++col) {
        matrix[row * m + col] = powers[row + col];
    }
    float error = 0;
    for (int i = 0; i < n; ++i) {
        error += pownf(points[i].x, row) * points[i].y;
    }
    errors[row] = error;
}
clock_end();
```

### debug
```
samples: 10000
cycles: 125819 avg 120420 best
ms: 0.034684 avg 0.028000 best
samples: 10000
cycles: 124391 avg 120348 best
ms: 0.034308 avg 0.031000 best
samples: 10000
cycles: 124605 avg 120420 best
ms: 0.034354 avg 0.033000 best
samples: 10000
cycles: 127579 avg 120600 best
ms: 0.035173 avg 0.032000 best
```
### release
```
samples: 10000
cycles: 102549 avg 96264 best
ms: 0.028172 avg 0.026000 best
samples: 10000
cycles: 103316 avg 96156 best
ms: 0.028430 avg 0.025000 best
samples: 10000
cycles: 98939 avg 95940 best
ms: 0.027211 avg 0.025000 best
samples: 10000
cycles: 101698 avg 96120 best
ms: 0.027971 avg 0.025000 best
```

### jest szybciej
ok. 10 razy

## dodajmy własną funkcję potęgi
### debug
```
samples: 10000
cycles: 420020 avg 406764 best
ms: 0.116187 avg 0.111000 best
samples: 10000
cycles: 422607 avg 408204 best
ms: 0.116971 avg 0.112000 best
samples: 10000
cycles: 420295 avg 408312 best
ms: 0.116333 avg 0.102000 best
samples: 10000
cycles: 419029 avg 408492 best
ms: 0.115991 avg 0.113000 best
```
### release
```
samples: 10000
cycles: 68148 avg 65268 best
ms: 0.018696 avg 0.017000 best
samples: 10000
cycles: 67473 avg 65268 best
ms: 0.018504 avg 0.016000 best
samples: 10000
cycles: 67534 avg 65124 best
ms: 0.018524 avg 0.016000 best
samples: 10000
cycles: 68253 avg 65412 best
ms: 0.018719 avg 0.016000 best
```

## dalsze rozbicie na części


## wypełnianie cache potęg
```c++
clock_start();
for (int pow = 0; pow < 2*m; ++pow) {
    float total = 0;
    for (int i = 0; i < n; ++i) {
        total += power_fi(points[i].x, pow);
        // total += pownf(points[i].x, pow);
    }
    powers[pow] = total;
}
clock_end();
```

### debug
```
samples: 10000
cycles: 337407 avg 327492 best
ms: 0.093372 avg 0.090000 best
```
### release
```
samples: 10000
cycles: 61379 avg 57600 best
ms: 0.016807 avg 0.014000 best
```

### znów mamy winowajcę
Większość czasu bloku wypełniania macierzy, jest tutaj

### analiza algorymtu
2m * n potęg
2 * m * m * n operacji mnożenia
2 * m * m * (m-1)
2 (m³ - m²) operacji mnożenia

2m * n  ->  2 (m² - m) operacji dodawania


## podejście inkrementacyjne - eliminacja potęgowania
```c++
clock_start();
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
clock_end();
```

### debug
```
samples: 10000
cycles: 23006 avg 21384 best
ms: 0.006192 avg 0.004000 best
samples: 10000
cycles: 23342 avg 21276 best
ms: 0.006276 avg 0.004000 best
samples: 10000
cycles: 23301 avg 21456 best
ms: 0.006283 avg 0.004000 best
samples: 10000
cycles: 23267 avg 21312 best
ms: 0.006265 avg 0.004000 best
```
### release
```
samples: 10000
cycles: 6546 avg 5364 best
ms: 0.001625 avg 0.000000 best
samples: 10000
cycles: 6418 avg 5436 best
ms: 0.001594 avg 0.000000 best
samples: 10000
cycles: 6423 avg 5220 best
ms: 0.001588 avg 0.000000 best
samples: 10000
cycles: 6315 avg 5364 best
ms: 0.001559 avg 0.000000 best
```

### 10-krotne przyspieszenie
Zamiast każdorazowo liczyć x^n, x^(n+1), ...
Obliczamy następną potęgę na podstawie poprzedniej: x^(n+1) = x^n * x
Usprawniamy złożoność obliczeniową 
ilość operacji mnożenia:
2m * n
2(m² - m)
ilość operacji dodawania:
2m * n + n
2m * (m-1) + m-1
2m² - m - 1


## wypełnianie macierzy
```c++
clock_start();
for (int row = 0; row < m; ++row) {
    swap_table[row] = row;

    for (int col = 0; col < m; ++col) {
        matrix[row * m + col] = sum_of_powers[row + col];
    }
}
clock_end();
```
### debug
```
samples: 10000
cycles: 11213 avg 9216 best
ms: 0.002846 avg 0.000000 best
samples: 10000
cycles: 11032 avg 9216 best
ms: 0.002860 avg 0.000000 best
samples: 10000
cycles: 11004 avg 9000 best
ms: 0.002860 avg 0.002000 best
samples: 10000
cycles: 11043 avg 9324 best
ms: 0.002870 avg 0.001000 best
```
### release
```
samples: 10000
cycles: 4021 avg 3240 best
ms: 0.000922 avg 0.000000 best
samples: 10000
cycles: 3972 avg 3132 best
ms: 0.000914 avg 0.000000 best
samples: 10000
cycles: 4029 avg 2916 best
ms: 0.000924 avg 0.000000 best
samples: 10000
cycles: 3995 avg 3096 best
ms: 0.000912 avg 0.000000 best
```

### szybciutko
Czas niewiele większy niż overhead benchamrku


## wypełnianie wektora błędów
```c++
clock_start();
for (int row = 0; row < m; ++row) {
    float error = 0;
    for (int i = 0; i < n; ++i) {
        error += power_fi(points[i].x, row) * points[i].y;
        // error += pownf(points[i].x, row) * points[i].y;
    }
    errors[row] = error;
}
clock_end();
```
### debug
```
samples: 10000
cycles: 77407 avg 75024 best
ms: 0.021263 avg 0.019000 best
samples: 10000
cycles: 77480 avg 75240 best
ms: 0.021263 avg 0.020000 best
samples: 10000
cycles: 77297 avg 75204 best
ms: 0.021254 avg 0.019000 best
samples: 10000
cycles: 77554 avg 75456 best
ms: 0.021311 avg 0.020000 best
```
### release
```
samples: 10000
cycles: 15688 avg 13428 best
ms: 0.004154 avg 0.002000 best
samples: 10000
cycles: 15495 avg 13500 best
ms: 0.004107 avg 0.002000 best
samples: 10000
cycles: 15313 avg 13500 best
ms: 0.004056 avg 0.001000 best
samples: 10000
cycles: 15065 avg 13536 best
ms: 0.003987 avg 0.002000 best
```

## eliminacja potęgowania z wektora błędów
stosując tę samą metodę przechowywania obecnej potęgi każdego z punktów w tablicy, eliminujemy kosztowne operacje mnożenia
```c++
clock_start();
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
clock_end();
```
### debug
```
samples: 10000
cycles: 13730 avg 12312 best
ms: 0.003610 avg 0.002000 best
samples: 10000
cycles: 14205 avg 12636 best
ms: 0.003702 avg 0.001000 best
samples: 10000
cycles: 13688 avg 12636 best
ms: 0.003587 avg 0.000000 best
samples: 10000
cycles: 13778 avg 12492 best
ms: 0.003618 avg 0.001000 best
```
### release
```
samples: 10000
cycles: 4839 avg 3888 best
ms: 0.001150 avg 0.000000 best
samples: 10000
cycles: 4755 avg 4032 best
ms: 0.001135 avg 0.000000 best
samples: 10000
cycles: 4782 avg 3744 best
ms: 0.001139 avg 0.000000 best
samples: 10000
cycles: 4807 avg 3924 best
ms: 0.001144 avg 0.000000 best
```
### bardzo dobry wynik
większość czasu to narzut z samego benchmarku
Możemy usunąć naszą funkcję potęgowania c:


## powrót do całej funkcji
### debug
```
samples: 10000
cycles: 227112 avg 219996 best
ms: 0.062745 avg 0.060000 best
samples: 10000
cycles: 226345 avg 219816 best
ms: 0.062483 avg 0.059000 best
samples: 10000
cycles: 226825 avg 220788 best
ms: 0.062675 avg 0.061000 best
samples: 10000
cycles: 226253 avg 220104 best
ms: 0.062492 avg 0.060000 best
```
### release
```
samples: 10000
cycles: 20354 avg 17460 best
ms: 0.005447 avg 0.003000 best
samples: 10000
cycles: 19150 avg 17244 best
ms: 0.005123 avg 0.003000 best
samples: 10000
cycles: 19586 avg 17424 best
ms: 0.005245 avg 0.003000 best
samples: 10000
cycles: 19994 avg 17568 best
ms: 0.005364 avg 0.002000 best
```

### poprawa ok. 47-krotna