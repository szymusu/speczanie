#include "format_polynomial.h"

#include <stdio.h>

void format_polynomial(char* dest, int max_length, const CurvePolynomial* curve) {
    int line_length = 0;
    for (int i = curve->order - 1; i > 0; --i) {
        char sep = ' ';
        if (line_length > 64) {
            sep = '\n';
            line_length = 0;
        }
        const int written = snprintf(dest, max_length, "%fx^%d%c+ ", curve->coefficients[i], i, sep);
        if (written >= max_length) return; // snprinf zwraca rozmiar tego co by napisał gdyby się zmieściło

        line_length += written;
        dest += written;
        max_length -= written;
    }
    snprintf(dest, max_length, "%.2f", curve->coefficients[0]);
}
