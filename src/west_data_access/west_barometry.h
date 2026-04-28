
#ifndef IDAM_PLUGIN_WEST_BAROMETRY_H
#define IDAM_PLUGIN_WEST_BAROMETRY_H

#include "tstype_tmp.h"

Longint barometry_gauge_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint barometry_gauge_type_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint barometry_gauge_type_index(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint barometry_gauge_type_description(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint barometry_gauge_pressure_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint barometry_gauge_pressure_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint barometry_gauge_calibration_coefficient(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
void barometry_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber);
#endif // IDAM_PLUGIN_WEST_BAROMETRY_H
