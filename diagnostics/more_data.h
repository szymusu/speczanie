#ifndef MORE_DATA_H
#define MORE_DATA_H

#include <raylib.h>

typedef struct {
    Vector2*  data;
    Vector2*  points;
    int count;

} DataAndPoints;

DataAndPoints create_sinus_data(int count, float offset);
void destroy_sinus_data(DataAndPoints* data);

#endif //MORE_DATA_H
