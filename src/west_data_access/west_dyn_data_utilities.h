#ifndef IDAM_PLUGIN_WEST_DYN_DATA_UTILITIES_H
#define IDAM_PLUGIN_WEST_DYN_DATA_UTILITIES_H


#include "tstype_tmp.h"

Longint SetNormalizedDynamicData(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes, char* normalizationAttributes);

Longint SetNormalizedDynamicDataTime(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes, char* normalizationAttributes);

Longint GetNormalizedDynamicData(Longint shotNumber, Double** time, Double** data, Longint* len, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes, char* normalizationAttributes);

Longint GetDynData(Longint shotNumber, Double** time, Double** data, Longint* len, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes);

void SetDynamicData(DATA_BLOCK* data_block, Longint len, Double *time, Double *data);

void SetDynamicDataTime(DATA_BLOCK* data_block, Longint len, Double *time, Double *data);

Longint time_field(const char *object_name, Longint shotNumber, Longint extractionIndex, Double **time, Double **data, Longint* len);

Longint getArcadeSignal(const char* nomsigp, Longint shotNumber, Longint extractionIndex, Double** time, Double** data, Longint* len, Double normalizationFactor);
void setReturnData2DDouble (DATA_BLOCK* data_block, Longint dim1_shape, Longint dim2_shape, Double* data);

Longint setUDABlockSignalFromArcade(const char* sigName, Longint shotNumber, Longint extractionIndex, DATA_BLOCK* data_block, Longint* nodeIndices, Double normalizationFactor);
Longint setUDABlockTimeFromArcade(const char* sigName, Longint shotNumber, Longint extractionIndex, DATA_BLOCK* data_block, Longint* nodeIndices);
void merge2Signals_according_to_ip_treshold(Double **data, Longint len, Double *data1, Double *data2, Double *ip, Double treshold);
Longint averageArcadeSignal(const char* sigName, Longint shotNumber, Longint extractions[], Longint extractions_length, Double** time, Double** averaged_data, Longint* len);

Longint signalsRatio(Double **result_q_by_r, Double *q, Double *r, Longint lenq, Longint lenr);
Longint signalsSquare(Double **square_s, Double *s, Longint len);
Longint multiplySignals(Double **result, Double *p, Double *q, Longint len);
Longint equals(Double *p, Double *q, Longint len);

void sum(Double* sum_data, Double* data, Longint len);
void substract(Double* diff_data, Double* data, Longint len);
void normalize(Double* sum_data, Longint len, Longint normalizationFactor);
void multiply(Double* data, Longint len, Double factor);


#endif // IDAM_PLUGIN_WEST_DYN_DATA_UTILITIES_H
