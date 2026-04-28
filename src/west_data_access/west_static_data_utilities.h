#ifndef IDAM_PLUGIN_WEST_STATIC_DATA_UTILITIES_H
#define IDAM_PLUGIN_WEST_STATIC_DATA_UTILITIES_H

#include "tstype_tmp.h"

//Longint setUDABlockFromArcadeScalarField(Longint data_type, char* prod_name, char* object_name, char* param_name, Longint index,
//		Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices, Double normalizationFactor);
void setStaticValue(Longint data_type, DATA_BLOCK* data_block, char* value, Longint requestedIndex, Double normalizationFactor);
void set_BTANG_StaticValue(Longint data_type, DATA_BLOCK* data_block, char* value, Longint requestedIndex, Double normalizationFactor);
void SetStatic1DData(DATA_BLOCK* data_block, Longint len, Double *data);
void SetStatic1DLongintData(DATA_BLOCK* data_block, Longint len, Longint *data);

#endif // IDAM_PLUGIN_WEST_DYN_DATA_UTILITIES_H
