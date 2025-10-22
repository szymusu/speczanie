#ifndef POINTHOVERTOOLTIP_H
#define POINTHOVERTOOLTIP_H
#include <raylib.h>

#include "../../data/point_data.h"

typedef struct {
    Vector2* data;
    Vector2* points;
    VisiblePointsInfo visible;

} PointHoverTooltipProps;

void PointHoverTooltip(PointHoverTooltipProps props);

#endif //POINTHOVERTOOLTIP_H
