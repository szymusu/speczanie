#ifndef REGRESSION_H
#define REGRESSION_H

#include "../plot/components/DataPlot.h"

void regression(CurvePolynomial* curve, Vector2* points, int point_count, int degree);
float normalize(Vector2* points, int count);

#endif //REGRESSION_H