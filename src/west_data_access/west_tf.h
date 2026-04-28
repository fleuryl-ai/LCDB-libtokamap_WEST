
#ifndef IDAM_PLUGIN_WEST_TF_H
#define IDAM_PLUGIN_WEST_TF_H


#include "tstype_tmp.h"

Longint tf_b_field_tor_vacuum_r_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint tf_delta_b_field_tor_vacuum_r_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint tf_b_field_tor_vacuum_r_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint tf_delta_b_field_tor_vacuum_r_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint tf_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

#endif // IDAM_PLUGIN_WEST_TF_H
