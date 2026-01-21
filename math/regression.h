#ifndef REGRESSION_H
#define REGRESSION_H

#include "../plot/components/DataPlot.h"

void regression(CurvePolynomial* curve, Vector2* points, int point_count, int degree);
float normalize(Vector2* points, int count);
int prepare_points_between(int i1, int i2, DataSource data_source, Vector2* regression_points, CurvePolynomial* curve);

#endif //REGRESSION_H