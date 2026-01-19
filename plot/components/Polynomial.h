#ifndef SPECZANIE_POLYNOMIAL_H
#define SPECZANIE_POLYNOMIAL_H

#include "DataPlot.h"

#define POLYNOMIAL_POINT_COUNT 100
#define POLYNOMIAL_MAX_DEGREE 30

void Polynomial(CurvePolynomial* curve, Vector2* points, int point_count, move_change_t change, Bounds bounds);

#endif //SPECZANIE_POLYNOMIAL_H