
#ifndef IDAM_PLUGIN_WEST_PF_PASSIVE_H
#define IDAM_PLUGIN_WEST_PF_PASSIVE_H

#include "tstype_tmp.h"

Longint pf_passive_loop_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_loop_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_element_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_element_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_elements_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_loops_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_turns(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_R(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_Z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_current_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint pf_passive_current_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
void pf_passive_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber);

#endif // IDAM_PLUGIN_WEST_PF_PASSIVE_H
