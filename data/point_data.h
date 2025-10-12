#ifndef POINT_DATA_H
#define POINT_DATA_H

#include <raylib.h>
#include "../plot/plot_math.h"

/**
 * @param data data points to transform
 * @param points destination for pixel values
 * @param count data point count
 * @param bounds current view bounds
 * @return size of visible points
 */
int translate_data_to_points(const Vector2* data, Vector2* points, int count, Bounds bounds);

#endif //POINT_DATA_H
