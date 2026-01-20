#include "format_polynomial.h"

#include <stdio.h>

void format_polynomial(char* dest, int max_length, const CurvePolynomial* curve) {
    for (int i = curve->order - 1; i > 0; --i) {
        const int written = snprintf(dest, max_length, "%.2fx^%d + ", curve->coefficients[i], i);
        dest += written;
        max_length -= written;
    }
    snprintf(dest, max_length, "%.2f", curve->coefficients[0]);
}
