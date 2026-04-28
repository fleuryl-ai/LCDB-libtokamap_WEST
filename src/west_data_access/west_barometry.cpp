#include "west_barometry.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"

void barometry_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber) {
	int err = 901;
	char msg[1000];
	sprintf(msg, "%s(%s),object:%s,shot:%ld,err:%ld\n", "WEST:ERROR", methodName, object_name, shotNumber, status);
	//UDA_LOG(UDA_LOG_ERROR, "%s", msg);
	addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
}

Longint barometry_gauge_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint status = -1;
	Longint gaugeId = nodeIndices[0]; //starts from 1
	if (gaugeId == 1) {
		const char* name = "Baratron divertor Haut Q2haut";
		//setReturnDataString(data_block, name, NULL);
		status = 0;
	} else if (gaugeId == 2) {
		const char* name = "Baratron divertor Q3 Baffle";
		//setReturnDataString(data_block, name, NULL);
		status = 0;
	} else if (gaugeId == 3) {
		const char* name = "Baratron divertor Q5A Baffle";
		//setReturnDataString(data_block, name, NULL);
		status = 0;
	}  else if (gaugeId == 4) {
		const char* name = "Jauge Penning Q5B Baffle(CF2P) + optical signal";
		//setReturnDataString(data_block, name, NULL);
		status = 0;
	} else {
		status = -1;
		barometry_throwsIdamError(status, "barometry_gauge_name", "unknown gauge", shotNumber);
	}
	return status;
}

Longint barometry_gauge_type_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint status = -1;
	Longint gaugeId = nodeIndices[0]; //starts from 1
	if (gaugeId == 1 || gaugeId == 2 || gaugeId == 3) {
		const char* name = "Baratron";
		////setReturnDataString(data_block, name, NULL);
		status = 0;
	}  else if (gaugeId == 4) {
		const char* name = "Penning";
		////setReturnDataString(data_block, name, NULL);
		status = 0;
	} else {
		barometry_throwsIdamError(status, "barometry_gauge_type_name", "unknown gauge", shotNumber);
	}
	return status;
}

Longint barometry_gauge_type_index(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint status = -1;
	Longint gaugeId = nodeIndices[0]; //starts from 1
	if (gaugeId == 1 || gaugeId == 2 || gaugeId == 3) {
		Longint index = 2;
		////setReturnDataIntScalar(data_block, index, NULL);
		status = 0;
	} else if (gaugeId == 4) {
		Longint index = 1;
		////setReturnDataIntScalar(data_block, index, NULL);
		status = 0;
	} else {
		barometry_throwsIdamError(status, "barometry_gauge_type_index", "unknown gauge", shotNumber);
	}
	return status;
}

Longint barometry_gauge_type_description(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	return barometry_gauge_name(shotNumber, data_block, nodeIndices);
}

Longint barometry_gauge_pressure_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	UDA_LOG(UDA_LOG_DEBUG, "Calling barometry_gauge_pressure_data\n");
	Double f = 1; //conversion factor
	Longint gaugeId = nodeIndices[0]; //starts from 1
	Longint status = -1;
	if (gaugeId == 1) {
		const char *object_name = "GBARDB4";
		Longint extractionIndex = 2;
		UDA_LOG(UDA_LOG_DEBUG, "Calling setUDABlockSignalFromArcade\n");
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
		UDA_LOG(UDA_LOG_DEBUG, "after Calling setUDABlockSignalFromArcade\n");
		if (status != 0) {
			barometry_throwsIdamError(status, "barometry_gauge_pressure_data", object_name, shotNumber);
		}
	} else if (gaugeId == 2) {
		const char *object_name = "GBARDB8";
		Longint extractionIndex = 5;
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
		if (status != 0) {
			barometry_throwsIdamError(status, "barometry_gauge_pressure_data", object_name, shotNumber);
		}
	} else if (gaugeId == 3) {
		const char *object_name = "GBARDB8";
		Longint extractionIndex = 12;
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
		if (status != 0) {
			barometry_throwsIdamError(status, "barometry_gauge_pressure_data", object_name, shotNumber);
		}
	} else if (gaugeId == 4) {
		const char *object_name = "GBARDP4";
		Longint extractionIndex = 6;
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
		if (status != 0) {
			barometry_throwsIdamError(status, "barometry_gauge_pressure_data", object_name, shotNumber);
		}
	}
	UDA_LOG(UDA_LOG_DEBUG, "Returning from barometry_gauge_pressure_data\n");
	return status;
}

Longint barometry_gauge_pressure_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	UDA_LOG(UDA_LOG_DEBUG, "calling barometry_gauge_pressure_time...\n");

	Longint len;
	Double *time = NULL;
	Double *data = NULL;
	Longint rang[2] = { 0, 0 };

	char nomsigp_to_extract[50];
	Longint gaugeId = nodeIndices[0]; //starts from 1
	Longint status = -1;

	if (gaugeId == 1) {
		const char* nomsigp = "GBARDB4";
		Longint extractionIndex = 2;
		addExtractionChars(nomsigp_to_extract, nomsigp, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
		status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time, &data, &len);
	} else if (gaugeId == 2) {
		const char* nomsigp = "GBARDB8";
		Longint extractionIndex = 5;
		addExtractionChars(nomsigp_to_extract, nomsigp, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
		status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time, &data, &len);
	} else if (gaugeId == 3) {
		const char* nomsigp = "GBARDB8";
		Longint extractionIndex = 12;
		addExtractionChars(nomsigp_to_extract, nomsigp, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
		status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time, &data, &len);
	}  else if (gaugeId == 4) {
		const char* nomsigp = "GBARDP4";
		Longint extractionIndex = 6;
		addExtractionChars(nomsigp_to_extract, nomsigp, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
		status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time, &data, &len);
	}

	UDA_LOG(UDA_LOG_DEBUG, "status in barometry_gauge_pressure_time = %ld...\n", status);

	if (status != 0) {
		free(time);
		free(data);
		barometry_throwsIdamError(status, "barometry_gauge_pressure_time", "GBARDB4/8", shotNumber);
		return status;

	}
	UDA_LOG(UDA_LOG_DEBUG, "setting time...\n");
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	UDA_LOG(UDA_LOG_DEBUG, "Returning from barometry_gauge_pressure_time...\n");
	return status;
}

Longint barometry_gauge_calibration_coefficient(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint status = -1;
	Longint gaugeId = nodeIndices[0]; //starts from 1
	if (gaugeId == 1) {
		Double calibration_coefficient = 3.9663*1e-5;
		//setReturnDataDoubleScalar(data_block, calibration_coefficient, NULL);
		status = 0;
	} else if (gaugeId == 2) {
		Double calibration_coefficient = 3.9663*1e-5;
		//setReturnDataDoubleScalar(data_block, calibration_coefficient, NULL);
		status = 0;
	} else if (gaugeId == 3) {
		Double calibration_coefficient = 3.9663*1e-5;
		//setReturnDataDoubleScalar(data_block, calibration_coefficient, NULL);
		status = 0;
	}  else if (gaugeId == 4) {
		Double no_calibration_coefficient_defined = -9.0*1e-40;
		//setReturnDataDoubleScalar(data_block, no_calibration_coefficient_defined, NULL);
		status = 0;
	}
	return status;
}

// #ifdef WEST_STANDALONE_TEST
// int main() {
// 	Longint nodeIndices [1] = {1};
// 	Longint shot = 62651;
// 	//DATA_BLOCK* db = NULL;
// 	auto data_block = (DATA_BLOCK*)calloc(1, sizeof(DATA_BLOCK));
// 	for (int i = 0; i < 2; i++) {
// 		nodeIndices[0] = i + 1;
		
// 		barometry_gauge_name(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "barometry_gauge_name");
// 		freeDataBlock(data_block);
// 		barometry_gauge_type_name(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "barometry_gauge_type_name");
// 		freeDataBlock(data_block);
// 		barometry_gauge_type_index(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "barometry_gauge_type_index");
// 		freeDataBlock(data_block);
// 		barometry_gauge_type_description(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "barometry_gauge_type_description");
// 		freeDataBlock(data_block);
// 		barometry_gauge_pressure_data(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "barometry_gauge_pressure_data");
// 		freeDataBlock(data_block);
// 		barometry_gauge_pressure_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "barometry_gauge_pressure_time");
// 		freeDataBlock(data_block);
// 		barometry_gauge_calibration_coefficient(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "barometry_gauge_calibration_coefficient");
// 		freeDataBlock(data_block);	
// 	}	

// 	return 0;
// }
// #endif