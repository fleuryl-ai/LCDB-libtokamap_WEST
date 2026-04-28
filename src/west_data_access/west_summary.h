
#ifndef IDAM_PLUGIN_WEST_SUMMARY_H
#define IDAM_PLUGIN_WEST_SUMMARY_H

#include "tstype_tmp.h"

Longint summary_global_quantities_beta_tor_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint summary_global_quantities_v_loop_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint summary_global_quantities_r0_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint summary_global_quantities_b0_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint summary_heating_current_drive_ec_power_source(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint summary_heating_current_drive_ec_power(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint summary_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ip_value(Double **ip_data, Double *ip_time, Longint *ip_len, Longint shotNumber, DATA_BLOCK* data_block, const Double treshold);
void summary_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber);
#endif // IDAM_PLUGIN_WEST_SUMMARY_H
