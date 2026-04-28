#include "west_tf.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"

void tf_throwsError(Longint status, const char* methodName, Longint shotNumber);

void tf_throwsError(Longint status, const char* methodName, Longint shotNumber) {
	int err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),shot:%ld,err:%ld\n", "WEST:ERROR", methodName, shotNumber,status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

Longint tf_b_field_tor_vacuum_r_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	const char* mapfun = "tsbase_collect;DMAG:GMAG_ITOR;1:Double:1;multiply:cste:-0.0073008";
	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetNormalizedDynamicData(shotNumber, &time, &data, &len, nodeIndices,
			TOP_collections_parameters, attributes, normalizationAttributes);
	if (status != 0) {
		free(fun_name);
		free(TOP_collections_parameters);
		free(attributes);
		free(normalizationAttributes);
		free(time);
		free(data);
		tf_throwsError(status, "tf_b_field_tor_vacuum_r_data_error_upper", shotNumber);
		return status;
	}
	Double dataMinValue = 6.*0.0073008;
	Double relative_error= 0.0001;
	maxValueOfAbs(data, len, dataMinValue, relative_error);

	SetDynamicData(data_block, len, time, data);
	free(fun_name);
	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);
	free(time);
	free(data);
	return 0;
}

Longint tf_delta_b_field_tor_vacuum_r_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

        char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
        char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
        char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
        char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

        const char* mapfun = "tsbase_collect;DMAG:GMAG_ITOR;2:Double:1;multiply:cste:-0.0073008";
        tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);

        Longint len;
        Double* time = NULL;
        Double* data = NULL;

        Longint status = GetNormalizedDynamicData(shotNumber, &time, &data, &len, nodeIndices,
                        TOP_collections_parameters, attributes, normalizationAttributes);
        if (status != 0) {
			free(fun_name);
			free(TOP_collections_parameters);
			free(attributes);
			free(normalizationAttributes);
			free(time);
			free(data);
            tf_throwsError(status, "tf_b_field_tor_vacuum_r_data_error_upper", shotNumber);
            return status;
        }
        Double dataMinValue = 0.05;
        Double relative_error= 0.0001;
        maxValueOfAbs(data, len, dataMinValue, relative_error);

        SetDynamicData(data_block, len, time, data);
		free(fun_name);
		free(TOP_collections_parameters);
		free(attributes);
		free(normalizationAttributes);
		free(time);
		free(data);
        return 0;
}

Longint tf_b_field_tor_vacuum_r_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	UDA_LOG(UDA_LOG_INFO, "Entering tf_b_field_tor_vacuum_r_data for shot: %ld\n", shotNumber);

	const char* mapfun = "tsbase_collect;DMAG:GMAG_ITOR;1:Double:1;multiply:cste:-0.0073008";
	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	UDA_LOG(UDA_LOG_INFO, "!!!!Calling %s for shot: %ld\n", fun_name, shotNumber);

	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetNormalizedDynamicData(shotNumber, &time, &data, &len, nodeIndices,
			TOP_collections_parameters, attributes, normalizationAttributes);
	if (status != 0) {
		free(fun_name);
		free(TOP_collections_parameters);
		free(attributes);
		free(normalizationAttributes);
		free(time);
		free(data);
		tf_throwsError(status, "tf_b_field_tor_vacuum_r_data", shotNumber);
		return status;
	}

	SetDynamicData(data_block, len, time, data);
	free(fun_name);
	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);
	free(time);
	free(data);
	return 0;
}

Longint tf_delta_b_field_tor_vacuum_r_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	UDA_LOG(UDA_LOG_INFO, "Entering tf_b_field_tor_vacuum_r_data for shot: %ld\n", shotNumber);

	const char* mapfun = "tsbase_collect;DMAG:GMAG_ITOR;2:Double:1;multiply:cste:-0.0073008";
	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	UDA_LOG(UDA_LOG_INFO, ">>>>Calling %s for shot: %ld\n", fun_name, shotNumber);

	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetNormalizedDynamicData(shotNumber, &time, &data, &len, nodeIndices,
			TOP_collections_parameters, attributes, normalizationAttributes);
	if (status != 0) {
		free(fun_name);
		free(TOP_collections_parameters);
		free(attributes);
		free(normalizationAttributes);
		free(time);
		free(data);
		tf_throwsError(status, "tf_b_field_tor_vacuum_r_data", shotNumber);
		return status;
	}

	SetDynamicData(data_block, len, time, data);
	free(fun_name);
	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);
	free(time);
	free(data);
	return 0;
}

Longint tf_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	UDA_LOG(UDA_LOG_INFO, "Entering tf_time for shot: %ld\n", shotNumber);
    
	const char* mapfun = "tsbase_time;DMAG:GMAG_ITOR;1:Double:1;multiply:cste:1";
	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	UDA_LOG(UDA_LOG_INFO, ">Calling %s for shot: %ld\n", fun_name, shotNumber);

	return SetNormalizedDynamicDataTime(shotNumber, data_block, nodeIndices, TOP_collections_parameters, attributes,
				normalizationAttributes);
}

// #ifdef WEST_STANDALONE_TEST
// int main() {
// 	Longint nodeIndices [1] = {1};
// 	Longint shot = 62651;
// 	//DATA_BLOCK* db = NULL;
// 	auto data_block = (DATA_BLOCK*)calloc(1, sizeof(DATA_BLOCK));
// 	for (int i = 0; i < 2; i++) {
// 		nodeIndices[0] = i + 1;
// 		tf_b_field_tor_vacuum_r_data_error_upper(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "tf_b_field_tor_vacuum_r_data_error_upper");
// 		freeDataBlock(data_block);
// 		tf_delta_b_field_tor_vacuum_r_data_error_upper(shot, data_block, nodeIndices);
// 		freeDataBlock(data_block);
// 		printDataBlockPreview(data_block, "tf_delta_b_field_tor_vacuum_r_data_error_upper");
// 	}	

// 	return 0;
// }
// #endif


