
#ifndef IDAM_PLUGIN_WEST_PF_ACTIVE_H
#define IDAM_PLUGIN_WEST_PF_ACTIVE_H

#include "tstype_tmp.h"

Longint pf_active_elements_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_coils_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_R(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_Z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_H(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_W(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_element_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_element_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_coil_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_coil_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_turns(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_current_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_current_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_active_coil_current_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
void pf_active_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber);
#endif // IDAM_PLUGIN_WEST_PF_ACTIVE_H
