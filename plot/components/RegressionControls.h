#ifndef SPECZANIE_REGRESSIONCONTROLS_H
#define SPECZANIE_REGRESSIONCONTROLS_H

#include "DataPlot.h"

typedef struct {
    CurvePolynomial* curve;
    int regression_point_count;
    move_change_t change;

} RegressionControlProps;

move_change_t RegressionControls(RegressionControlProps props);

#endif //SPECZANIE_REGRESSIONCONTROLS_H