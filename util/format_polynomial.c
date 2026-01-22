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

// void format_polynomial(char* dest, int max_length, const CurvePolynomial* curve) {
//     int written = snprintf(dest, max_length, "%.2fx^%d", curve->coefficients[curve->order - 1], curve->order - 1);
//     dest += written;
//     max_length -= written;
//
//     for (int i = curve->order - 2; i > 0; --i) {
//         written = snprintf(dest, max_length, " + %.2fx^%d", curve->coefficients[i], i);
//         dest += written;
//         max_length -= written;
//         if (i % 5 == 0) {
//             written = snprintf(dest, max_length, "\n");
//             dest += written;
//             max_length -= written;
//         }
//     }
//     if (curve->order > 1) {
//         written = snprintf(dest, max_length, " + ");
//         dest += written;
//         max_length -= written;
//     }
//     snprintf(dest, max_length, "%.2f", curve->coefficients[0]);
// }
