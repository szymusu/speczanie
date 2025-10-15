#ifndef POINT_DATA_H
#define POINT_DATA_H

#include <raylib.h>

#include "data_source.h"
#include "../plot/plot_math.h"

/**
 * @param data_source
 * @param points destination for pixel values
 * @param bounds current view bounds
 * @return size of visible points
 */
int translate_data_to_points(DataSource data_source, Vector2* points, Bounds bounds);

#endif //POINT_DATA_H
