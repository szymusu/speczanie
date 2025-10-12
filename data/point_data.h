#ifndef POINT_DATA_H
#define POINT_DATA_H

#include <raylib.h>
#include "../plot/plot_math.h"

void translate_data_to_points(const Vector2* data, Vector2* points, int count, Bounds bounds);

#endif //POINT_DATA_H
