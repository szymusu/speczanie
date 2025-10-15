#ifndef MORE_DATA_H
#define MORE_DATA_H

#include "../data/data_source.h"

DataSource create_sinus_data(int count, float offset);
void destroy_sinus_data(DataSource* data);

#endif //MORE_DATA_H
