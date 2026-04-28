#include "west_ic_antennas.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"

//#include "Include_tslib_w32.h"
#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"

void ic_antennas_throwsIdamError(Longint status, const char* methodName, const char * objectName, Longint shotNumber);
void ic_antennas_throwsIdamError1(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId);
void ic_antennas_throwsIdamError2(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId, Longint moduleId, Longint matching_element);
void ic_antennas_throwsIdamError3(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId, Longint moduleId, Longint currentId);
void ic_antennas_throwsIdamError4(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId, Longint moduleId, Longint voltageId);
void ic_antennas_throwsIdamError5(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId, Longint moduleId);

void ic_antennas_throwsIdamError(Longint status, const char* methodName, const char * objectName, Longint shotNumber) {
	int err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),object:%s,shot:%ld,err:%ld\n", "WEST:ERROR", methodName, objectName, shotNumber,status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

void ic_antennas_throwsIdamError1(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId) {
	int err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),object:%s,shot:%ld,antennaId:%ld,err:%ld\n", "WEST:ERROR", methodName, objectName, shotNumber, antennaId, status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

void ic_antennas_throwsIdamError2(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId, Longint moduleId, Longint matching_element) {
	int err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),object:%s,shot:%ld,antenna:%ld,module:%ld,matching_element:%ld,err:%ld\n", "WEST:ERROR", methodName, objectName, shotNumber,antennaId, moduleId, matching_element, status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

void ic_antennas_throwsIdamError3(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId, Longint moduleId, Longint currentId) {
	int err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),object:%s,shot:%ld,antenna:%ld,module:%ld,current:%ld,err:%ld\n", "WEST:ERROR", methodName, objectName, shotNumber,antennaId, moduleId, currentId, status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

void ic_antennas_throwsIdamError4(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId, Longint moduleId, Longint voltageId) {
	int err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),object:%s,shot:%ld,antenna:%ld,module:%ld,voltage:%ld,err:%ld\n", "WEST:ERROR", methodName, objectName, shotNumber,antennaId, moduleId, voltageId, status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

void ic_antennas_throwsIdamError5(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId, Longint moduleId) {
	int err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),object:%s,shot:%ld,antenna:%ld,module:%ld,err:%ld\n", "WEST:ERROR", methodName, objectName, shotNumber,antennaId, moduleId, status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

Longint ic_antennas_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint antennaId = nodeIndices[0];
	if (antennaId == 1) {
		const char* name = "Q1";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (antennaId == 2) {
		const char* name = "Q2";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (antennaId == 3) {
		const char* name = "Q4";
		//setReturnDataString(data_block, name, NULL);
	}
	return 0;
}

Longint ic_antennas_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	return ic_antennas_name(shotNumber, data_block, nodeIndices);
}

Longint ic_antennas_module_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint moduleId = nodeIndices[1];
	if (moduleId == 1) {
		const char* name = "left";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (moduleId == 2) {
		const char* name = "right";
		//setReturnDataString(data_block, name, NULL);
	}
	return 0;
}

Longint ic_antennas_module_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	return ic_antennas_module_name(shotNumber, data_block, nodeIndices);
}

Longint ic_antennas_module_pressure_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];

	Longint cases[3][2] = {1,2,3,4,5,6};

	Longint c = cases[antennaId - 1][moduleId - 1];

	if (c == 1) {
		const char* name = "Q1 left";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (c == 2) {
		const char* name = "Q1 right";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (c == 3) {
		const char* name = "Q2 left";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (c == 4) {
		const char* name = "Q2 right";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (c == 5) {
		const char* name = "Q4 left";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (c == 6) {
		const char* name = "Q4 right";
		//setReturnDataString(data_block, name, NULL);
	}
	return 0;
}

Longint ic_antennas_module_pressure_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	return ic_antennas_module_pressure_name(shotNumber, data_block, nodeIndices);
}

/*
 * matching capacitor values [pF] (1: Q1 left upper, 2: Q1 left lower, 3:
 * Q1 right upper, 4:Q1 right lower; 5: Q2 left upper, 6: Q2 left lower, 7:
 * Q2 right upper, 8:Q2 right lower; 9: Q4 left upper, 10: Q4 left lower, 11:
 * Q4 right upper, 12:Q4 right lower) module/matching_element/capacitance
 */

Longint ic_antennas_module_matching_element_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint matching_element = nodeIndices[2];

	Longint extractionIndices[3][2][2] = {1,2,3,4,5,6,7,8,9,10,11,12};

	Longint extractionIndex = extractionIndices[antennaId - 1] [moduleId - 1] [matching_element - 1];
	if (extractionIndex == 1) {
		const char* name = "Q1 left upper";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 2) {
		const char* name = "Q1 left lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 3) {
		const char* name = "Q1 right upper";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 4) {
		const char* name = "Q1 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 5) {
		const char* name = "Q2 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 6) {
		const char* name = "Q2 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 7) {
		const char* name = "Q2 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 8) {
		const char* name = "Q2 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 9) {
		const char* name = "Q4 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 10) {
		const char* name = "Q4 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 11) {
		const char* name = "Q4 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	else if (extractionIndex == 12) {
		const char* name = "Q4 right lower";
		//setReturnDataString(data_block, name, NULL);
	}
	return 0;
}

Longint ic_antennas_module_matching_element_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	return ic_antennas_module_matching_element_name(shotNumber, data_block, nodeIndices);
}

Longint ic_antennas_module_power_forward(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1e3; //conversion factor, power is given in MW in Arcade
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;
	Longint extractionIndex = 0;
	if (moduleId == 1) { //left
		extractionIndex = 1;
	}
	else { //right
		extractionIndex = 3;
	}
	if (antennaId == 1) { //Q1 antenna
		const char *object_name = "GICHANTPOWQ1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 2) { //Q2 antenna
		const char *object_name = "GICHANTPOWQ2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 3) { //Q3 antenna
		const char *object_name = "GICHANTPOWQ4";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		ic_antennas_throwsIdamError5(status, "ic_antennas_power_forward", "GICHANTPOWQ1/GICHANTPOWQ2/GICHANTPOWQ4", shotNumber, antennaId, moduleId);
	}
	return status;
}

Longint ic_antennas_module_power_forward_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;
	Longint extractionIndex = 0;
	if (moduleId == 1) { //left
		extractionIndex = 1;
	}
	else { //right
		extractionIndex = 3;
	}
	if (antennaId == 1) { //Q1 antenna
		const char *object_name = "GICHANTPOWQ1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 2) { //Q2 antenna
		const char *object_name = "GICHANTPOWQ2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 3) { //Q3 antenna
		const char *object_name = "GICHANTPOWQ4";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError5(status, "ic_antennas_module_power_forward_time", "GICHANTPOWQ1/GICHANTPOWQ2/GICHANTPOWQ4", shotNumber, antennaId, moduleId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_module_power_reflected(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1e3; //conversion factor, power is given in kW in Arcade
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;
	Longint extractionIndex = 0;
	if (moduleId == 1) { //left
		extractionIndex = 2;
	}
	else { //right
		extractionIndex = 4;
	}
	if (antennaId == 1) {
		const char *object_name = "GICHANTPOWQ1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 2) {
		const char *object_name = "GICHANTPOWQ2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 3) {
		const char *object_name = "GICHANTPOWQ4";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		ic_antennas_throwsIdamError5(status, "ic_antennas_power_reflected","GICHANTPOWQ1/GICHANTPOWQ2/GICHANTPOWQ4", shotNumber, antennaId, moduleId);
	}
	return status;
}

Longint ic_antennas_module_power_reflected_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;
	Longint extractionIndex = 0;
	if (moduleId == 1) { //left
		extractionIndex = 2;
	}
	else { //right
		extractionIndex = 4;
	}
	if (antennaId == 1) {
		const char *object_name = "GICHANTPOWQ1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 2) {
		const char *object_name = "GICHANTPOWQ2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 3) {
		const char *object_name = "GICHANTPOWQ4";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError5(status, "ic_antennas_power_reflected_time","GICHANTPOWQ1/GICHANTPOWQ2/GICHANTPOWQ4", shotNumber, antennaId, moduleId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_module_phase_forward(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 3.1415926535897932384626433832795/180.; //conversion factor, from deg to rad
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;
	Longint extractionIndex = 1;
	if (moduleId == 1) { //left
		//phase = 0, reference
		Double *time = NULL;
		Double *data = NULL;
		Longint len;
		if (antennaId == 1) { //Q1 antenna
			const char *object_name = "GICHPHASESQ1";
			status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		}
		else if (antennaId == 2) { //Q2 antenna
			const char *object_name = "GICHPHASESQ2";
			status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		}
		else if (antennaId == 3) { //Q3 antenna
			const char *object_name = "GICHPHASESQ4";
			status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		}
		if (status != 0) {
			free(time);
			free(data);
			ic_antennas_throwsIdamError5(status, "ic_antennas_module_phase_forward", "GICHPHASESQ1/GICHPHASESQ2/GICHPHASESQ4", shotNumber, antennaId, moduleId);
			return status;
		}
		//We create a null vector with length = len(time)
		data = (Double*) malloc(sizeof(Double)*len);
		Longint i;
		for (i = 0; i < len; i++)
			data[i] = 0.0;
		SetDynamicData(data_block, len, time, data);
		free(time);
		free(data);
	}
	else {
		if (antennaId == 1) { //Q1 antenna
			const char *object_name = "GICHPHASESQ1";
			status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
		}
		else if (antennaId == 2) { //Q2 antenna
			const char *object_name = "GICHPHASESQ2";
			status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
		}
		else if (antennaId == 3) { //Q3 antenna
			const char *object_name = "GICHPHASESQ4";
			status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
		}
		if (status != 0) {
			ic_antennas_throwsIdamError5(status, "ic_antennas_module_phase_forward", "GICHPHASESQ1/GICHPHASESQ2/GICHPHASESQ4", shotNumber, antennaId, moduleId);
			return status;
		}
	}
	return 0;
}

Longint ic_antennas_module_phase_forward_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;
	Longint extractionIndex = 1;

	if (antennaId == 1) { //Q1 antenna
		const char *object_name = "GICHPHASESQ1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 2) { //Q2 antenna
		const char *object_name = "GICHPHASESQ2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 3) { //Q3 antenna
		const char *object_name = "GICHPHASESQ4";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError5(status, "ic_antennas_module_phase_forward_time", "GICHPHASESQ1/GICHPHASESQ2/GICHPHASESQ4", shotNumber, antennaId, moduleId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_module_phase_reflected(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 3.1415926535897932384626433832795/180.; //conversion factor, from deg to rad
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;
	Longint extractionIndex;
	if (moduleId == 1) { //left
		extractionIndex = 2;
	}
	else { //right
		extractionIndex = 5;
	}
	if (antennaId == 1) { //Q1 antenna
		const char *object_name = "GICHPHASESQ1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 2) { //Q2 antenna
		const char *object_name = "GICHPHASESQ2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 3) { //Q3 antenna
		const char *object_name = "GICHPHASESQ4";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		ic_antennas_throwsIdamError5(status, "ic_antennas_module_phase_reflected", "GICHPHASESQ1/GICHPHASESQ2/GICHPHASESQ4", shotNumber, antennaId, moduleId);
	}
	return status;
}

Longint ic_antennas_module_phase_reflected_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;
	Longint extractionIndex;
	if (moduleId == 1) { //left
		extractionIndex = 2;
	}
	else { //right
		extractionIndex = 5;
	}
	if (antennaId == 1) { //Q1 antenna
		const char *object_name = "GICHPHASESQ1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 2) { //Q2 antenna
		const char *object_name = "GICHPHASESQ2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 3) { //Q3 antenna
		const char *object_name = "GICHPHASESQ4";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError5(status, "ic_antennas_module_phase_reflected_time", "GICHPHASESQ1/GICHPHASESQ2/GICHPHASESQ4", shotNumber, antennaId, moduleId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_module_voltage_phase(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 3.1415926535897932384626433832795/180.; //conversion factor, from deg to rad
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint voltageId = nodeIndices[2];
	Longint status = -1;

	Longint extractionIndices[2][2] = {3, 4, 6, 7};
	/*extractionIndices[0][0] = 3;
		extractionIndices[0][1] = 4;
		extractionIndices[1][0] = 6;
		extractionIndices[1][1] = 7;*/
	Longint extractionIndex = extractionIndices[moduleId - 1][voltageId - 1];

	if (antennaId == 1) { //Q1 antenna
		const char *object_name = "GICHPHASESQ1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 2) { //Q2 antenna
		const char *object_name = "GICHPHASESQ2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 3) { //Q3 antenna
		const char *object_name = "GICHPHASESQ4";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}

	if (status != 0) {
		ic_antennas_throwsIdamError4(status, "ic_antennas_module_voltage_phase", "GICHPHASESQ1/GICHPHASESQ2/GICHPHASESQ4", shotNumber, antennaId, moduleId, voltageId);
	}
	return status;
}

Longint ic_antennas_module_voltage_phase_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint voltageId = nodeIndices[2];
	Longint status = -1;

	Longint extractionIndices[2][2] = {3, 4, 6, 7};
	/*extractionIndices[0][0] = 3;
	extractionIndices[0][1] = 4;
	extractionIndices[1][0] = 6;
	extractionIndices[1][1] = 7;*/

	Longint extractionIndex = extractionIndices[moduleId - 1][voltageId - 1];

	if (antennaId == 1) { //Q1 antenna
		const char *object_name = "GICHPHASESQ1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 2) { //Q2 antenna
		const char *object_name = "GICHPHASESQ2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 3) { //Q3 antenna
		const char *object_name = "GICHPHASESQ4";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError4(status, "ic_antennas_module_voltage_phase_time", "GICHPHASESQ1/GICHPHASESQ2/GICHPHASESQ4", shotNumber, antennaId, moduleId, voltageId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_module_current(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1.0; //conversion factor
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint currentId = nodeIndices[2];
	Longint status = -1;

	//first index = antennaId
	//second index = moduleId
	//third index = currentId
	Longint extractionIndices[3][2][2] = {1,2,3,4,5,6,7,8,9,10,11,12};

	//first antenna
	//first module --> 'left'
	//extractionIndices[0,0,0] = 1; //upper
	//extractionIndices[0,0,1] = 2; //lower
	//first antenna
	//second module --> 'right'
	//extractionIndices[0,1,0] = 3; //upper
	//extractionIndices[0,1,1] = 4; //lower
	//second antenna
	//first module --> 'left'
	//extractionIndices[1,0,0] = 5; //upper
	//extractionIndices[1,0,1] = 6; //lower
	//second antenna
	///second module --> 'right'
	//extractionIndices[1,1,0] = 7; //upper
	//extractionIndices[1,1,1] = 8; //lower
	//third antenna
	//first module --> 'left'
	//extractionIndices[2,0,0] = 9; //upper
	//extractionIndices[2,0,1] = 10; //lower
	//third antenna
	//second module --> 'right'
	//extractionIndices[2,1,0] = 11; //upper
	//extractionIndices[2,1,1] = 12; //lower
	//Longint *ptr_extractionIndices = extractionIndices[0,0,0];
	//Longint extractionIndex = extractionIndices[antennaId - 1, moduleId - 1, currentId - 1];
	Longint extractionIndex = extractionIndices[antennaId - 1][moduleId - 1][currentId - 1];
	const char *object_name = "GICHICAPA";
	status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);

	if (status != 0) {
		ic_antennas_throwsIdamError3(status, "ic_antennas_module_current","GICHICAPA", shotNumber, antennaId, moduleId, currentId);
	}
	return status;
}

Longint ic_antennas_module_current_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint currentId = nodeIndices[2];
	Longint status = -1;

	//first index = antennaId
	//second index = moduleId
	//third index = currentId
	Longint extractionIndices[3][2][2] = {1,2,3,4,5,6,7,8,9,10,11,12};

	//first antenna
	//first module --> 'left'
	//extractionIndices[0,0,0] = 1; //upper
	//extractionIndices[0,0,1] = 2; //lower
	//first antenna
	//second module --> 'right'
	//extractionIndices[0,1,0] = 3; //upper
	//extractionIndices[0,1,1] = 4; //lower
	//second antenna
	//first module --> 'left'
	//extractionIndices[1,0,0] = 5; //upper
	//extractionIndices[1,0,1] = 6; //lower
	//second antenna
	///second module --> 'right'
	//extractionIndices[1,1,0] = 7; //upper
	//extractionIndices[1,1,1] = 8; //lower
	//third antenna
	//first module --> 'left'
	//extractionIndices[2,0,0] = 9; //upper
	//extractionIndices[2,0,1] = 10; //lower
	//third antenna
	//second module --> 'right'
	//extractionIndices[2,1,0] = 11; //upper
	//extractionIndices[2,1,1] = 12; //lower

	Longint extractionIndex = extractionIndices[antennaId - 1][moduleId - 1][currentId - 1];
	const char *object_name = "GICHICAPA";
	status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);

	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError3(status, "ic_antennas_module_current_time","GICHICAPA", shotNumber, antennaId, moduleId, currentId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_module_voltage(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1.e3; //conversion factor from kV to V
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint voltageId = nodeIndices[2];
	Longint status = -1;

	//first index = moduleId
	//second index = voltageId
	Longint extractionIndices[2][2] = {1,2,3,4};
	//first module --> 'left'
	//extractionIndices[0,0] = 1; //upper
	//extractionIndices[0,1] = 2; //lower
	//second module --> 'right'
	//extractionIndices[1,0] = 3; //upper
	//extractionIndices[1,1] = 4; //lower

	Longint extractionIndex = extractionIndices[moduleId - 1][voltageId - 1];

	if (antennaId == 1) {
		const char *object_name = "GICHVPROBEQ1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 2) {
		const char *object_name = "GICHVPROBEQ2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else if (antennaId == 3) {
		const char *object_name = "GICHVPROBEQ4";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		ic_antennas_throwsIdamError4(status, "ic_antennas_module_voltage","GICHVPROBEQ1/GICHVPROBEQ2/GICHVPROBEQ4", shotNumber, antennaId, moduleId, voltageId);
	}
	return status;
}

Longint ic_antennas_module_voltage_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint voltageId = nodeIndices[2];
	Longint status = -1;

	//first index = moduleId
	//second index = voltageId
	Longint extractionIndices[2][2] = {1,2,3,4};
	//first module --> 'left'
	//extractionIndices[0,0] = 1; //upper
	//extractionIndices[0,1] = 2; //lower
	//second module --> 'right'
	//extractionIndices[1,0] = 3; //upper
	//extractionIndices[1,1] = 4; //lower
	//Longint *ptr_extractionIndices = extractionIndices[0,0];
	Longint extractionIndex = extractionIndices[moduleId - 1][voltageId - 1];

	if (antennaId == 1) {
		const char *object_name = "GICHVPROBEQ1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 2) {
		const char *object_name = "GICHVPROBEQ2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	else if (antennaId == 3) {
		const char *object_name = "GICHVPROBEQ4";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}
	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError4(status, "ic_antennas_module_voltage","GICHVPROBEQ1/GICHVPROBEQ2/GICHVPROBEQ4", shotNumber, antennaId, moduleId, voltageId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_module_matching_element_capacity(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1.e-12; //conversion factor
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint matching_element = nodeIndices[2];
	Longint status = -1;

	//first index = antennaId
	//second index = moduleId
	//third index = matching_element
	Longint extractionIndices[3][2][2] = {1,2,3,4,5,6,7,8,9,10,11,12};

	//first antenna
	//first module --> 'left'
	//extractionIndices[0,0,0] = 1; //upper
	//extractionIndices[0,0,1] = 2; //lower
	//first antenna
	//second module --> 'right'
	//extractionIndices[0,1,0] = 3; //upper
	//extractionIndices[0,1,1] = 4; //lower
	//second antenna
	//first module --> 'left'
	//extractionIndices[1,0,0] = 5; //upper
	//extractionIndices[1,0,1] = 6; //lower
	//second antenna
	///second module --> 'right'
	//extractionIndices[1,1,0] = 7; //upper
	//extractionIndices[1,1,1] = 8; //lower
	//third antenna
	//first module --> 'left'
	//extractionIndices[2,0,0] = 9; //upper
	//extractionIndices[2,0,1] = 10; //lower
	//third antenna
	//second module --> 'right'
	//extractionIndices[2,1,0] = 11; //upper
	//extractionIndices[2,1,1] = 12; //lower

	Longint extractionIndex = extractionIndices[antennaId - 1] [moduleId - 1] [matching_element - 1];
	const char *object_name = "GICHCAPA";
	status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);

	if (status != 0) {
		ic_antennas_throwsIdamError2(status, "ic_antennas_module_matching_element_capacity","GICHCAPA", shotNumber, antennaId, moduleId, matching_element);
	}
	return status;
}

Longint ic_antennas_module_matching_element_capacity_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint matching_element = nodeIndices[2];
	Longint status = -1;

	//first index = antennaId
	//second index = moduleId
	//third index = matching_element
	Longint extractionIndices[3][2][2] = {1,2,3,4,5,6,7,8,9,10,11,12};
	//first antenna
	//first module --> 'left'
	//extractionIndices[0,0,0] = 1; //upper
	//extractionIndices[0,0,1] = 2; //lower
	//first antenna
	//second module --> 'right'
	//extractionIndices[0,1,0] = 3; //upper
	//extractionIndices[0,1,1] = 4; //lower
	//second antenna
	//first module --> 'left'
	//extractionIndices[1,0,0] = 5; //upper
	//extractionIndices[1,0,1] = 6; //lower
	//second antenna
	///second module --> 'right'
	//extractionIndices[1,1,0] = 7; //upper
	//extractionIndices[1,1,1] = 8; //lower
	//third antenna
	//first module --> 'left'
	//extractionIndices[2,0,0] = 9; //upper
	//extractionIndices[2,0,1] = 10; //lower
	//third antenna
	//second module --> 'right'
	//extractionIndices[2,1,0] = 11; //upper
	//extractionIndices[2,1,1] = 12; //lower
	//Longint *ptr_extractionIndices = extractionIndices[0,0,0];
	Longint extractionIndex = extractionIndices[antennaId - 1][moduleId - 1][matching_element - 1];
	const char *object_name = "GICHCAPA";
	status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);

	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError2(status, "ic_antennas_module_matching_element_capacity_time","GICHCAPA", shotNumber, antennaId, moduleId, matching_element);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_module_pressure(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1.0; //conversion factor
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;

	//first index = antennaId
	//second index = moduleId
	Longint extractionIndices[3][2] = {1,2,3,4,5,6};

	//first antenna
	//first module --> 'left'
	//extractionIndices[0,0] = 1;
	//first antenna
	//second module --> 'right'
	//extractionIndices[0,1] = 2;
	//second antenna
	//first module --> 'left'
	//extractionIndices[1,0] = 3; //upper
	//second antenna
	///second module --> 'right'
	//extractionIndices[1,1] = 4;
	//third antenna
	//first module --> 'left'
	//extractionIndices[2,0] = 5;
	//third antenna
	//second module --> 'right'
	//extractionIndices[2,1] = 6;
	Longint extractionIndex = extractionIndices[antennaId - 1][moduleId - 1];
	const char *object_name = "GICHVTRANSFO";
	status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);

	if (status != 0) {
		ic_antennas_throwsIdamError5(status, "ic_antennas_pressure","GICHVTRANSFO", shotNumber, antennaId, moduleId);
		return status;
	}
	return status;
}

Longint ic_antennas_module_pressure_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint status = -1;

	//first index = antennaId
	//second index = moduleId
	Longint extractionIndices[3][2] = {1,2,3,4,5,6};

	//first antenna
	//first module --> 'left'
	//extractionIndices[0,0] = 1;
	//first antenna
	//second module --> 'right'
	//extractionIndices[0,1] = 2;
	//second antenna
	//first module --> 'left'
	//extractionIndices[1,0] = 3; //upper
	//second antenna
	///second module --> 'right'
	//extractionIndices[1,1] = 4;
	//third antenna
	//first module --> 'left'
	//extractionIndices[2,0] = 5;
	//third antenna
	//second module --> 'right'
	//extractionIndices[2,1] = 6;
	Longint extractionIndex = extractionIndices[antennaId - 1][moduleId - 1];
	const char *object_name = "GICHVTRANSFO";
	status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);

	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError5(status, "ic_antennas_module_pressure_time","GICHVTRANSFO", shotNumber, antennaId, moduleId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_power_launched(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1.e3; //conversion factor
	Longint antennaId = nodeIndices[0];
	Longint status = -1;

	Longint extractionIndex = 1;
	if (antennaId == 1) {
		const char *object_name = "SICHPQ1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	} else if (antennaId == 2) {
		const char *object_name = "SICHPQ2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	} else if (antennaId == 3) {
		const char *object_name = "SICHPQ4";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}

	if (status != 0) {
		ic_antennas_throwsIdamError1(status, "ic_antennas_power","SICHPQ1/SICHPQ2/SICHPQ4", shotNumber, antennaId);
	}
	return status;
}

Longint ic_antennas_power_launched_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0];
	Longint status = -1;

	Longint extractionIndex = 1;
	if (antennaId == 1) {
		const char *object_name = "SICHPQ1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	} else if (antennaId == 2) {
		const char *object_name = "SICHPQ2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	} else if (antennaId == 3) {
		const char *object_name = "SICHPQ4";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
	}

	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError1(status, "ic_antennas_power_launched_time","SICHPQ1/SICHPQ2/SICHPQ4", shotNumber, antennaId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_frequency(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Longint antennaId = nodeIndices[0];
	Longint val_nb = 3;
	Longint nb_val = 0;
	char* value = NULL;
	//Reading the antennas frequencies (3 scalars for Q1, Q2 and Q4)
	int format;
	Longint status = tsrqparm(&value, &nb_val, shotNumber, "DFCI", "PILOTAGE", "ICHFREQ", val_nb, &format);
	if (status != 0) {
		free(value);
		ic_antennas_throwsIdamError1(status, "ic_antennas_frequency","DFCI:PILOTAGE:ICHFREQ", shotNumber, antennaId);
		
		return status;
	}
        if (format != REEL32 && format != REEL16) {
           int err = 901; 
           UDA_LOG(UDA_LOG_ERROR, "WEST:ERROR: ic_antennas_frequency: Unexpected datatype returned by tsrqparm!");
           addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: ic_antennas_frequency: Unexpected datatype returned by tsrqparm!", err, "");
        }
        
        Double* pt_Double;
        
        if (format == REEL16) {
             pt_Double = (Double*) malloc(sizeof(Double)*val_nb);
             int i = 0;
             float *pt_float = (float*) value;
             for (i = 0; i < val_nb; i++) {
                 pt_Double[i] = (Double) pt_float[i];
             }    
        }
        else if (format == REEL32) {
             pt_Double = (Double*)value;
        }
	//Double* pt_Double = (Double*)value;

	//Getting the time vector
	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	if (antennaId == 1) {
		status = time_field("GICHANTPOWQ1", shotNumber, 1, &time, &data, &len);
	}
	else if (antennaId == 2) {
		status = time_field("GICHANTPOWQ2", shotNumber, 1, &time, &data, &len);
	}
	else if (antennaId == 3) {
		status = time_field("GICHANTPOWQ4", shotNumber, 1, &time, &data, &len);
	}

	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError1(status, "ic_antennas_frequency","GICHANTPOWQ1,GICHANTPOWQ2,GICHANTPOWQ3", shotNumber, antennaId);
		return status;
	}
	//Building the FLT_1D antenna/frequency field
	Double* frequencies = (Double*) malloc(sizeof(Double)*len);
	Longint i = 0;
	Double f = 1.e6; //conversion factor from MHz to Hz
	for (i = 0; i < len; i++) {
		frequencies[i] = f*pt_Double[antennaId - 1]; //vector filled with the same value (frequency is constant in time)
	}

	SetDynamicData(data_block, len, time, frequencies);
	free(pt_Double);
	free(data);
	free(time);
	return 0;
}

Longint ic_antennas_frequency_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint antennaId = nodeIndices[0];
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	const char* object_name = "GICHANTPOWQ1";
	Longint status = time_field(object_name, shotNumber, 1, &time, &data, &len);
	if (status != 0) {
		free(time);
		free(data);
		ic_antennas_throwsIdamError1(status, "ic_antennas_frequency_time","GICHANTPOWQ1%1", shotNumber, antennaId);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint ic_antennas_modules_strap_phase_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint strapId = nodeIndices[2];

	Double f = 3.1415926535897932384626433832795/180.; //conversion factor, from deg to rad

	Longint status = -1;
	Longint len1;
	Longint len4;
	Longint len5;
	Longint len6;
	Longint len7;

	Double *time1 = NULL;
	Double *data1 = NULL;

	Double *time4 = NULL;
	Double *data4 = NULL;

	Double *time5 = NULL;
	Double *data5 = NULL;

	Double *time6 = NULL;
	Double *data6 = NULL;

	Double *time7 = NULL;
	Double *data7 = NULL;

	Longint rang[2] = { 0, 0 };

	char* table_name;
	if (antennaId == 1) {
		const char* name = "GICHPHASESQ1";
		table_name = strdup(name);
	}
	else if (antennaId == 2) {
		const char* name = "GICHPHASESQ2";
		table_name = strdup(name);
	}
	else if (antennaId == 3) {
		const char* name = "GICHPHASESQ4";
		table_name = strdup(name);
	}

	char nomsigp_to_extract[50];

	Longint extractionIndex = 1;
	addExtractionChars(nomsigp_to_extract, table_name, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time1, &data1, &len1);

	if (status != 0) {
		free(time1);
		free(data1);
		free(time4);
		free(data4);
		free(time5);
		free(data5);
		free(time6);
		free(data6);
		free(time7);
		free(data7);
		free(table_name);
		ic_antennas_throwsIdamError5(status, "ic_antennas_modules_strap_phase_data", "A1", shotNumber, antennaId, moduleId);
		return status;
	}
	multiply(data1, len1, f);

	extractionIndex = 4;
	addExtractionChars(nomsigp_to_extract, table_name, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time4, &data4, &len4);

	if (status != 0) {
		free(time1);
		free(data1);
		free(time4);
		free(data4);
		free(time5);
		free(data5);
		free(time6);
		free(data6);
		free(time7);
		free(data7);
		free(table_name);
		ic_antennas_throwsIdamError5(status, "ic_antennas_modules_strap_phase_data", "A4", shotNumber, antennaId, moduleId);
		return status;
	}
	multiply(data4, len4, f);

	extractionIndex = 5;
	addExtractionChars(nomsigp_to_extract, table_name, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time5, &data5, &len5);

	if (status != 0) {
		free(time1);
		free(data1);
		free(time4);
		free(data4);
		free(time5);
		free(data5);
		free(time6);
		free(data6);
		free(time7);
		free(data7);
		free(table_name);
		ic_antennas_throwsIdamError5(status, "ic_antennas_modules_strap_phase_data", "A5", shotNumber, antennaId, moduleId);
		return status;
	}
	multiply(data5, len5, f);

	extractionIndex = 6;
	addExtractionChars(nomsigp_to_extract, table_name, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time6, &data6, &len6);

	if (status != 0) {
		free(time1);
		free(data1);
		free(time4);
		free(data4);
		free(time5);
		free(data5);
		free(time6);
		free(data6);
		free(time7);
		free(data7);
		free(table_name);
		ic_antennas_throwsIdamError5(status, "ic_antennas_modules_strap_phase_data", "A6", shotNumber, antennaId, moduleId);
		return status;
	}
	multiply(data6, len6, f);

	extractionIndex = 7;
	addExtractionChars(nomsigp_to_extract, table_name, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, &time7, &data7, &len7);

	if (status != 0) {
		free(time1);
		free(data1);
		free(time4);
		free(data4);
		free(time5);
		free(data5);
		free(time6);
		free(data6);
		free(time7);
		free(data7);
		free(table_name);
		ic_antennas_throwsIdamError5(status, "ic_antennas_modules_strap_phase_data", "A7", shotNumber, antennaId, moduleId);
		return status;
	}
	multiply(data7, len7, f);

	if (moduleId == 1 && strapId == 1) {
		sum(data1, data4, len1);
		SetDynamicData(data_block, len1, time1, data1);
	}
	else if (moduleId == 1 && strapId == 2)
	{
		sum(data1, data5, len1);
		SetDynamicData(data_block, len1, time1, data1);
	}
	else if (moduleId == 2 && strapId == 1)
	{
		SetDynamicData(data_block, len6, time6, data6);
	}
	else if (moduleId == 2 && strapId == 2)
	{
		SetDynamicData(data_block, len7, time7, data7);
	}

	free(table_name);
	free(time1);
	free(data1);
	free(time4);
	free(data4);
	free(time5);
	free(data5);
	free(time6);
	free(data6);
	free(time7);
	free(data7);
	return 0;

}

Longint ic_antennas_modules_strap_phase_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	//Longint strapId = nodeIndices[2];

	Longint status = -1;
	Longint len;

	Double *time = NULL;
	Double *data = NULL;

	Longint rang[2] = { 0, 0 };

	char* table_name;
	if (antennaId == 1) {
		const char* name = "GICHPHASESQ1";
		table_name = strdup(name);
	}
	else if (antennaId == 2) {
		const char* name = "GICHPHASESQ2";
		table_name = strdup(name);
	}
	else if (antennaId == 3) {
		const char* name = "GICHPHASESQ4";
		table_name = strdup(name);
	}

	char nomsigp_to_extract[50];

	Longint extractionIndex = 1;
	status = time_field(table_name, shotNumber, extractionIndex, &time, &data, &len);

	if (status != 0) {
		free(time);
		free(data);
		free(table_name);
		ic_antennas_throwsIdamError5(status, "ic_antennas_modules_strap_phase_time", "TIME", shotNumber, antennaId, moduleId);
		return status;
	}

	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	free(table_name);
	return 0;
}

Longint ic_antennas_modules_strap_outline_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint antennaId = nodeIndices[0];
	//Longint moduleId = nodeIndices[1];
	//Longint strapId = nodeIndices[2];

	Longint val_nb = 3;
	Longint nb_val = 0;
	char* value = NULL;
        int format;
	//Calling tsmat(shot, 'EXP=T=S;Position;PosICRH');
	Longint status = tsrqparm(&value, &nb_val, shotNumber, "EXP-T-S", "Position", "PosICRH", val_nb, &format);
	if (status != 0) {
		free(value);
		ic_antennas_throwsIdamError(status, "ic_antennas_modules_strap_outline_r","EXP=T=S:Position:PosICRH", shotNumber);
		return status;
	}

        Double* r0;

        if (format == REEL16) {
             r0 = (Double*) malloc(sizeof(Double)*val_nb);
             int i = 0;
             float *pt_float = (float*) value;
             for (i = 0; i < val_nb; i++) {
                 r0[i] = (Double) pt_float[i];
             }
        }
        else if (format == REEL32) {
             r0 = (Double*)value;
        }

	const int N = 6; //number of radial positions of a strap (2 straps for the left module, 2 straps for the right module)
	Double* r = (Double*) malloc(sizeof(Double)*N);
	r[0] = r0[antennaId - 1] + 9.e-3;
	r[1] = r0[antennaId - 1] + 44.e-3;
	r[2] = r0[antennaId - 1] + 58.e-3;
	r[3] = r0[antennaId - 1] + 87.e-3;
	r[4] = r0[antennaId - 1] + 116.e-3;
	r[5] = r0[antennaId - 1] + 140.e-3;
        
        //UDA_LOG(UDA_LOG_DEBUG, "TEST::Value of antennaId = %d\n", antennaId);
        //UDA_LOG(UDA_LOG_DEBUG, "TEST::Value of r0 = %f\n", r0[antennaId - 1]);
	SetStatic1DData(data_block, N, r);
	free(r0);
	free(r);
	return 0;
}

Longint ic_antennas_modules_strap_outline_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	//Longint antennaId = nodeIndices[0];
	Longint strapId = nodeIndices[2];
	const int N = 6; //number of radial positions of a strap (2 straps for the left module, 2 straps for the right module)
	Double* z = (Double*) malloc(sizeof(Double)*N);
	z[0] = 296.e-3;
	z[1] = 160.e-3;
	z[2] = 45.e-3;
	z[3] = 22.e-3;
	z[4] = 22.e-3;
	z[5] = 52.e-3;
	if (strapId == 2) { //we change the sign of z (inferior strap)
		Longint i;
		for (i = 0; i < N; i++) {
			z[i] = - z[i];
		}
	}
	SetStatic1DData(data_block, N, z);
	free(z);
	return 0;
}

Longint ic_antennas_modules_strap_outline_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Longint antennaId = nodeIndices[0];
	Longint moduleId = nodeIndices[1];
	Longint strapId = nodeIndices[2];

	/*Q1 :
	ic_antennas%antenna(1)%module(1)%strap(1)%outline%phi = 35°
	ic_antennas%antenna(1)%module(1)%strap(2)%outline%phi = 35°
	ic_antennas%antenna(1)%module(2)%strap(1)%outline%phi = 45°
	ic_antennas%antenna(1)%module(2)%strap(2)%outline%phi = 45°

	Q2 :
	ic_antennas%antenna(2)%module(1)%strap(1)%outline%phi = 95°
	ic_antennas%antenna(2)%module(1)%strap(2)%outline%phi = 95°
	ic_antennas%antenna(2)%module(2)%strap(1)%outline%phi = 105°
	ic_antennas%antenna(2)%module(2)%strap(2)%outline%phi = 105°

	Q4:
	ic_antennas%antenna(3)%module(1)%strap(1)%outline%phi = 195°
	ic_antennas%antenna(3)%module(1)%strap(2)%outline%phi = 195°
	ic_antennas%antenna(3)%module(2)%strap(1)%outline%phi = 205°
	ic_antennas%antenna(3)%module(2)%strap(2)%outline%phi = 205°*/
	Double f = 3.1415926535897932384626433832795/180.;
	/*Double phi[3][2][2] = {f*35, f*35, f*45, f*45, f*95, f*95, f*105, f*105, f*195, f*195, f*205, f*205};

	phi[0][0][0] = f*35; //radians
	phi[0][0][1] = f*35;
	phi[0][1][0] = f*45;
	phi[0][1][1] = f*45;

	phi[1][0][0] = f*95; //radians
	phi[1][0][1] = f*95;
	phi[1][1][0] = f*105;
	phi[1][1][1] = f*105;

	phi[2][0][0] = f*195; //radians
	phi[2][0][1] = f*195;
	phi[2][1][0] = f*205;
	phi[2][1][1] = f*205;
        */

        Double phi[3][2] = {f*35, f*45, f*95, f*105, f*195, f*205};

        const int N = 6;
        Double *p = (Double*) malloc(sizeof(Double) * N);
        p[0] = phi[antennaId - 1][moduleId - 1];
        int i = 0;
        for (i = 1; i < N; i++) {
           p[i] = p[0];
        } 
        
	SetStatic1DData(data_block, N, p);
    free(p);
        
	return 0;
}

Longint ic_antennas_modules_strap_width_tor(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double width_tor = 0.13;
	//setReturnDataDoubleScalar(data_block, width_tor, NULL);
	return 0;
}

Longint ic_antennas_modules_strap_distance_to_conductor(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double distance_to_conductor = 0.14;
	//setReturnDataDoubleScalar(data_block, distance_to_conductor, NULL);
	return 0;
}

Longint ic_antennas_ids_properties_comment(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	const char* comment = "The value of the field antenna(:)%module(:)%strap(:)%distance_to_conductor is approximately the distance between the front face of the strap and the antenna box. This distance is approximate since it is NOT constant according to the poloidal position.\n The value of antenna(:)%module(:)%strap(:)%outline%phi is currently NOT corrected from the radial position of the strap corners.";
	//on garde les valeurs de phi approchées données plus haut pour les 4 coins du strap
	//setReturnDataString(data_block, comment, NULL);
	return 0;
}
