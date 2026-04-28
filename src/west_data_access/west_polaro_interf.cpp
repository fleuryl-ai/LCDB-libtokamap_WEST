#include "west_polaro_interf.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"
#include "west_xml.h"

void polaro_throwsError(Longint status, const char* methodName, Longint shotNumber);

void polaro_throwsError(Longint status, const char* methodName, Longint shotNumber) {
	int err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),shot:%ld,err:%ld\n", "WEST:ERROR", methodName, shotNumber,status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

Longint polaro_or_interfero_channel_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint channelID = nodeIndices[0]; //starts from 1
	char channel_name[10];
	sprintf(channel_name, "%ld", channelID);
	//setReturnDataString(data_block, &channel_name[0], NULL);
	return 0;
}

//<mapping key="interferometer/channel/#/line_of_sight/first_point/r" value="tsmat_collect;DINTRPOL:LIDRT:RPOS2;0:float:#0" type="static"/>
Longint interferometer_channel_line_of_sight_first_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:RPOS2;0:float:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "set_value_collect;DINTRPOL:LIDRT:CHANNEL:Id:#0;0:string:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_setvalue_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}


Longint polarimeter_channel_line_of_sight_first_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:RPOS2;0:float:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_line_of_sight_first_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:ZPOS2;0:float:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_line_of_sight_first_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:TPOS2;0:float:#0;multiply:cste:0.017453292519943295";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_line_of_sight_second_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:RPOS1;0:float:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_line_of_sight_second_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:ZPOS1;0:float:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_line_of_sight_second_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:TPOS1;0:float:#0;multiply:cste:0.017453292519943295";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_line_of_sight_third_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:RPOS2;0:float:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}


Longint polarimeter_channel_line_of_sight_third_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:ZPOS2;0:float:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_line_of_sight_third_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsmat_collect;DINTRPOL:LIDRT:TPOS2;0:float:#0;multiply:cste:0.017453292519943295";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	Longint status = execute_tsmat_collect(TOP_collections_parameters, attributes, shotNumber, nodeIndices, normalizationAttributes);
	return status;
}

Longint polarimeter_channel_faraday_angle_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsbase_collect;DINTRPOL:GINTFARART;1:Double:#0";

	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetNormalizedDynamicData(shotNumber, &time, &data, &len, nodeIndices,
			TOP_collections_parameters, attributes, normalizationAttributes);
	if (status != 0) {
		//free(fun_name);
		free(TOP_collections_parameters);
		free(attributes);
		free(normalizationAttributes);
		free(time);
		free(data);
		polaro_throwsError(status, "polarimeter_channel_faraday_angle_data", shotNumber);
		return status;
	}

	SetDynamicData(data_block, len, time, data);
	//free(fun_name);
	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);
	free(time);
	free(data);
	return 0;
}

Longint polarimeter_channel_faraday_angle_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	UDA_LOG(UDA_LOG_INFO, "Entering tf_time for shot: %ld\n", shotNumber);
    
	const char* mapfun = "tsbase_time;DINTRPOL:GINTFARART;1:Double:#0";
	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
	UDA_LOG(UDA_LOG_INFO, ">Calling %s for shot: %ld\n", fun_name, shotNumber);

	return SetNormalizedDynamicDataTime(shotNumber, data_block, nodeIndices, TOP_collections_parameters, attributes,
				normalizationAttributes);

	return 0;
}

Longint interferometer_channel_n_e_line_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example : attributes = rank:Double:#1 (rank=0,1 , type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)
	const char* mapfun = "tsbase_collect_with_channels;unvalid_channels:2:1,2;DINTRPOL:GINTLIDRT;1:Double:#0;multiply:cste:2e19";

	//tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	char* unvalid_channels = NULL; //used for interfero_polarimeter IDS, example : invalid_channels:1,2
		tokenizeFunParametersWithChannels(mapfun, &unvalid_channels, &TOP_collections_parameters, &attributes,
				&normalizationAttributes);
		//freeTokenizedFunParameters(&unvalid_channels, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetNormalizedDynamicData(shotNumber, &time, &data, &len, nodeIndices,
			TOP_collections_parameters, attributes, normalizationAttributes);
	if (status != 0) {
		//free(fun_name);
		free(TOP_collections_parameters);
		free(attributes);
		free(normalizationAttributes);
		free(time);
		free(data);
		polaro_throwsError(status, "interferometer_channel_n_e_line_data", shotNumber);
		return status;
	}

	SetDynamicData(data_block, len, time, data);
	//free(fun_name);
	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);
	free(time);
	free(data);
	return 0;
}

Longint interferometer_channel_n_e_line_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {


	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	UDA_LOG(UDA_LOG_INFO, "Entering tf_time for shot: %ld\n", shotNumber);
	
	const char* mapfun = "tsbase_time_with_channels;unvalid_channels:2:1,2;DINTRPOL:GINTLIDRT;1:Double:#0";
	//tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	char* unvalid_channels = NULL; //used for interfero_polarimeter IDS, example : invalid_channels:1,2
			tokenizeFunParametersWithChannels(mapfun, &unvalid_channels, &TOP_collections_parameters, &attributes,
					&normalizationAttributes);
			//freeTokenizedFunParameters_2(&unvalid_channels, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	//UDA_LOG(UDA_LOG_INFO, ">Calling %s for shot: %ld\n", fun_name, shotNumber);

	return SetNormalizedDynamicDataTime(shotNumber, data_block, nodeIndices, TOP_collections_parameters, attributes,
				normalizationAttributes);

	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);

	return 0;
}


// #ifdef WEST_STANDALONE_TEST
// int main() {
// 	Longint nodeIndices [1] = {1};
// 	Longint shot = 62651;
// 	auto data_block = (DATA_BLOCK*)calloc(1, sizeof(DATA_BLOCK));
// 	for (int i = 0; i < 2; i++) {
// 		nodeIndices[0] = i + 1;
// 		interferometer_channel_line_of_sight_first_point_r(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "interferometer_channel_line_of_sight_first_point_r");
// 		freeDataBlock(data_block);
// 	}	
// 	return 0;
// }
// #endif
