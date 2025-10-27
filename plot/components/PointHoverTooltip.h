#ifndef POINTHOVERTOOLTIP_H
#define POINTHOVERTOOLTIP_H
#include <raylib.h>

#include "../../data/point_data.h"

typedef struct {
    Vector2* data;
    Vector2* points;
    VisiblePointsInfo visible;
    int index;

} PointHoverTooltipProps;

void PointHoverTooltip(PointHoverTooltipProps props);
int find_hover_point(const Vector2* points, int count);

#endif //POINTHOVERTOOLTIP_H
