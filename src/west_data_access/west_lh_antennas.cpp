#include "west_lh_antennas.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"

void lh_antennas_throwsIdamError(Longint status, const char* methodName, const char * objectName, Longint shotNumber) {
	Longint err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),object:%s,shot:%ld,err:%ld\n", "WEST:ERROR", methodName, objectName, shotNumber,status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

void lh_antennas_throwsIdamError2(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId) {
	Longint err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),object:%s,shot:%ld,antenna:%ld,err:%ld\n", "WEST:ERROR", methodName, objectName, shotNumber,antennaId, status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

Longint lh_antennas_ids_properties_comment(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	const char* comment = "LH total coupled power [MW] antenna[i=1,2].power_launched are currently computed as power_forward - power_reflected.";
	//on garde les valeurs de phi approchées données plus haut pour les 4 coins du strap
	//setReturnDataString(data_block, comment, NULL);
	return 0;
}

Longint lh_antennas_power(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	UDA_LOG(UDA_LOG_DEBUG, "Calling lh_antennas_power\n");
	Longint extractionIndex = 0; //indicates that signal does not belong to a group
	Double f = 1e6; //conversion factor, power is given in MW in Arcade
	const char *object_name = "SHYBPTOT";
	Longint status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	if (status != 0) {
		lh_antennas_throwsIdamError(status, "lh_antennas_power", object_name, shotNumber);
	}
	UDA_LOG(UDA_LOG_DEBUG, "Returning from lh_antennas_power\n");
	return status;
}

Longint lh_antennas_power_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	const char* object_name = "SHYBPTOT";
	Longint status = time_field(object_name, shotNumber, 1, &time, &data, &len);
	if (status != 0) {
		lh_antennas_throwsIdamError(status, "lh_antennas_power_time", object_name, shotNumber);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_antenna_power(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	UDA_LOG(UDA_LOG_DEBUG, "Calling lh_antennas_antenna_power\n");

	Longint antennaId = nodeIndices[0]; //=1 or 2
	Double f = 1e3; //conversion factor, power is given in kW in Arcade
	Double *forward_time = NULL;
	Double *forward_data = NULL;
	Longint forward_len;

	Longint status = -1;
	Longint extractionIndex = 0;

	if (antennaId == 1) {
		const char *object_name = "SHYBPFORW1";
		status = getArcadeSignal(object_name, shotNumber, extractionIndex,
				&forward_time, &forward_data, &forward_len, f);
	}
	else {
		const char *object_name = "SHYBPFORW2";
		status = getArcadeSignal(object_name, shotNumber, extractionIndex,
				&forward_time, &forward_data, &forward_len, f);
	}

	if (status != 0) {
		free(forward_time);
		free(forward_data);
		lh_antennas_throwsIdamError(status,"lh_antennas_antenna_power", "SHYBPFORW1/SHYBPFORW2", shotNumber);
		return status;
	}

	Double *reflected_time = NULL;
	Double *reflected_data = NULL;
	Longint reflected_len;

	if (antennaId == 1) {
		const char *object_name = "SHYBPREFL1";
		status = getArcadeSignal(object_name, shotNumber, extractionIndex,
				&reflected_time, &reflected_data, &reflected_len, f);
	}
	else {
		const char *object_name = "SHYBPREFL2";
		status = getArcadeSignal(object_name, shotNumber, extractionIndex,
				&reflected_time, &reflected_data, &reflected_len, f);
	}

	if (status != 0) {
		free(forward_time);
		free(forward_data);
		free(reflected_time);
		free(reflected_data);
		lh_antennas_throwsIdamError(status,"lh_antennas_antenna_power", "SHYBPREFL1/SHYBPREFL2", shotNumber);
		return status;
	}

	if (forward_len != reflected_len) {
		free(forward_time);
		free(forward_data);
		free(reflected_time);
		free(reflected_data);
		lh_antennas_throwsIdamError(status,"lh_antennas_antenna_power", "Reflected power data has not the same length than forward power data !", shotNumber);
		return -1;
	}

	substract(forward_data, reflected_data, forward_len);
	SetDynamicData(data_block, forward_len, forward_time, forward_data);
	free(forward_time);
	free(forward_data);
	free(reflected_time);
	free(reflected_data);
	return 0;

}

Longint lh_antennas_antenna_power_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Longint antennaId = nodeIndices[0]; //=1 or 2
	Double f = 1e3; //conversion factor, power is given in kW in Arcad
	Double *forward_time = NULL;
	Double *forward_data = NULL;
	Longint forward_len;

	Longint status = -1;
	Longint extractionIndex = 0;

	if (antennaId == 1) {
		const char *object_name = "SHYBPFORW1";
		status = getArcadeSignal(object_name, shotNumber, extractionIndex,
				&forward_time, &forward_data, &forward_len, f);
	}
	else {
		const char *object_name = "SHYBPFORW2";
		status = getArcadeSignal(object_name, shotNumber, extractionIndex,
				&forward_time, &forward_data, &forward_len, f);
	}

	if (status != 0) {
		free(forward_time);
		free(forward_data);
		lh_antennas_throwsIdamError(status,"lh_antennas_antenna_power_time", "SHYBPFORW1/SHYBPFORW2", shotNumber);
		return status;
	}

	Double *reflected_time = NULL;
	Double *reflected_data = NULL;
	Longint reflected_len;

	if (antennaId == 1) {
		const char *object_name = "SHYBPREFL1";
		status = getArcadeSignal(object_name, shotNumber, extractionIndex,
				&reflected_time, &reflected_data, &reflected_len, f);
	}
	else {
		const char *object_name = "SHYBPREFL2";
		status = getArcadeSignal(object_name, shotNumber, extractionIndex,
				&reflected_time, &reflected_data, &reflected_len, f);
	}

	if (status != 0) {
		free(forward_time);
		free(forward_data);
		free(reflected_time);
		free(reflected_data);
		lh_antennas_throwsIdamError(status,"lh_antennas_antenna_power_time", "SHYBPREFL1/SHYBPREFL2", shotNumber);
		
		return status;
	}

	if (forward_len != reflected_len) {
		free(forward_time);
		free(forward_data);
		free(reflected_time);
		free(reflected_data);
		lh_antennas_throwsIdamError(status,"lh_antennas_antenna_power_time", "Reflected power data has not the same length than forward power data !", shotNumber);
		return -1;
	}

	SetDynamicDataTime(data_block, forward_len, forward_time, forward_data);
	free(forward_time);
	free(forward_data);
	free(reflected_time);
	free(reflected_data);

	return 0;

}

Longint lh_antennas_power_forward(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1e3; //conversion factor, power is given in kW in Arcade
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint status = -1;
	Longint extractionIndex = 0; //indicates that signal does not belong to a group
	if (antennaId == 1) {
		const char *object_name = "SHYBPFORW1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "SHYBPFORW2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_power_forward", "SHYBPFORW1/SHYBPFORW2", shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_power_forward_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	Longint status = -1;
	if (antennaId == 1) {
		const char *object_name = "SHYBPFORW1";
		status = time_field(object_name, shotNumber, 1, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_power_forward_time", object_name, shotNumber);
			return status;
		}
	}
	else {
		const char *object_name = "SHYBPFORW2";
		status = time_field(object_name, shotNumber, 1, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_power_forward_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_power_reflected(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1e3; //conversion factor, power is given in MW in Arcade
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint extractionIndex = 0; //indicates that signal does not belong to a group
	Longint status = -1;
	if (antennaId == 1) {
		const char *object_name = "SHYBPREFL1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "SHYBPREFL2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_power_reflected","SHYBPREFL1/SHYBPREFL2", shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_power_reflected_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	Longint status = -1;
	if (antennaId == 1) {
		const char *object_name = "SHYBPREFL1";
		status = time_field(object_name, shotNumber, 1, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_power_reflected_time", object_name, shotNumber);
			return status;
		}
		
	}
	else {
		const char *object_name = "SHYBPREFL2";
		status = time_field(object_name, shotNumber, 1, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_power_reflected_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_reflection_coefficient(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Double f = 1; //conversion factor, power is given in MW in Arcade
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint extractionIndex = 0; //indicates that signal does not belong to a group
	Longint status = -1;
	if (antennaId == 1) {
		const char *object_name = "SHYBREF1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "SHYBREF2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_reflection_coefficient","SHYBREF1/SHYBREF2", shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_reflection_coefficient_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	Longint status = -1;
	if (antennaId == 1) {
		const char *object_name = "SHYBREF1";
		status = time_field(object_name, shotNumber, 1, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_reflection_coefficient_time", object_name, shotNumber);
			return status;
		}
	}
	else {
		const char *object_name = "SHYBREF2";
		status = time_field(object_name, shotNumber, 1, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_reflection_coefficient_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_position_definition(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	const char* comment = "Closest to machine geometric axis poLongint of the lateral antenna protection at Z = 0";
	//setReturnDataString(data_block, comment, NULL);
	return 0;
}

Longint lh_antennas_pressure_tank(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 1e-3; //conversion factor, pressure is given in mPa in Arcade
	Longint antennaId = nodeIndices[0]; //=1 or 2
	const char *object_name = "GPRESHYB";
	Longint status = setUDABlockSignalFromArcade(object_name, shotNumber, antennaId, data_block, nodeIndices, f);
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_pressure_tank", object_name, shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_pressure_tank_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	const char* object_name = "GPRESHYB";
	Longint status = time_field(object_name, shotNumber, antennaId, &time, &data, &len);
	if (status != 0) {
		free(time);
		free(data);
		lh_antennas_throwsIdamError(status, "lh_antennas_pressure_tank_time", object_name, shotNumber);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_phase_average(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 0.01745329251994329576923690768489; //conversion factor from degrees to radians
	Longint antennaId = nodeIndices[0]; //=1 or 2
	const char *object_name = "GPHASHYB";
	Longint status = setUDABlockSignalFromArcade(object_name, shotNumber, antennaId, data_block, nodeIndices, f);
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_phase_average", object_name, shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_phase_average_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	const char* object_name = "GPHASHYB";
	Longint status = time_field(object_name, shotNumber, antennaId, &time, &data, &len);
	if (status != 0) {
		free(time);
		free(data);
		lh_antennas_throwsIdamError(status, "lh_antennas_phase_average_time", object_name, shotNumber);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_n_parallel_peak(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 1;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	const char *object_name = "GNPARHYB";
	Longint status = setUDABlockSignalFromArcade(object_name, shotNumber, antennaId, data_block, nodeIndices, f);
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_n_parallel_peak", object_name, shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_n_parallel_peak_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	const char* object_name = "GNPARHYB";
	Longint status = time_field(object_name, shotNumber, antennaId, &time, &data, &len);
	if (status != 0) {
		free(time);
		free(data);
		lh_antennas_throwsIdamError(status, "lh_antennas_n_parallel_peak_time", object_name, shotNumber);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_position_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 1;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	const char *object_name = "GPOSHYB";
	Longint status = setUDABlockSignalFromArcade(object_name, shotNumber, antennaId, data_block, nodeIndices, f);
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_position_r", object_name, shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_position_r_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	const char* object_name = "GPOSHYB";
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint status = time_field(object_name, shotNumber, antennaId, &time, &data, &len);
	if (status != 0) {
		free(time);
		free(data);
		lh_antennas_throwsIdamError(status, "lh_antennas_position_r_time", object_name, shotNumber);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_position_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint status = -1;
	lh_antennas_throwsIdamError(status, "lh_antennas_position_z", "NOT IMPLEMENTED !!!", shotNumber);
	return status; //NOT IMPLEMENTED
}

Longint lh_antennas_modules_power(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 1e3; //conversion factor, power is given in MW in Arcade
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPINJC1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "GPINJC2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_modules_power", "GPINJC1/GPINJC2", shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_modules_power_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPINJC1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_power_time", object_name, shotNumber);
			return status;
		}
	}
	else {
		const char *object_name = "GPINJC2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_power_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_modules_power_forward(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 1e3; //conversion factor, power is given in MW in Arcade
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPFORWC1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "GPFORWC2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_modules_power_forward", "GPFORWC1/GPFORWC2", shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_modules_power_forward_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPFORWC1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_power_forward_time", object_name, shotNumber);
			return status;
		}
	}
	else {
		const char *object_name = "GPFORWC2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_power_forward_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_modules_power_launched(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 1e3; //conversion factor, power is given in kW in Arcade
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPINJC1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "GPINJC2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_modules_power_launched", "GPINJC1/GPINJC2", shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_modules_power_launched_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPINJC1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_power_launched_time", object_name, shotNumber);
			return status;
		}
	}
	else {
		const char *object_name = "GPINJC2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_power_launched_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_modules_power_reflected(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 1e3; //conversion factor, power is given in kW in Arcade
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPREFLC1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "GPREFLC2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_modules_power_reflected", "GPREFLC1/GPREFLC2", shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_modules_power_reflected_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint len;
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPREFLC1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_power_reflected_time", object_name, shotNumber);
			
			return status;
		}
	}
	else {
		const char *object_name = "GPREFLC2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_power_reflected_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_modules_reflection_coefficient(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 1;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GCREFC1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "GCREFC2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_modules_reflection_coefficient", "GCREFC1/GCREFC2", shotNumber,antennaId);
	}
	return status;
}

Longint lh_antennas_modules_reflection_coefficient_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint extractionIndex = nodeIndices[1]; //module id
	Longint len;
	Longint status = -1;
	if (antennaId == 1) {
		const char *object_name = "GCREFC1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_reflection_coefficient_time", object_name, shotNumber);
			return status;
		}
	}
	else {
		const char *object_name = "GCREFC2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_reflection_coefficient_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint lh_antennas_modules_phase(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double f = 0.01745329251994329576923690768489; //conversion factor from degrees to radians
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint status = -1;
	Longint extractionIndex = nodeIndices[1]; //module id
	if (antennaId == 1) {
		const char *object_name = "GPHIC1";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	else {
		const char *object_name = "GPHIC2";
		status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, f);
	}
	if (status != 0) {
		lh_antennas_throwsIdamError2(status, "lh_antennas_modules_phase", "GPHIC1/GPHIC2", shotNumber, antennaId);
	}
	return status;
}

Longint lh_antennas_modules_phase_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Double *time = NULL;
	Double *data = NULL;
	Longint antennaId = nodeIndices[0]; //=1 or 2
	Longint extractionIndex = nodeIndices[1]; //module id
	Longint len;
	Longint status = -1;
	if (antennaId == 1) {
		const char *object_name = "GPHIC1";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_phase_time", object_name, shotNumber);
			return status;
		}
	}
	else {
		const char *object_name = "GPHIC2";
		status = time_field(object_name, shotNumber, extractionIndex, &time, &data, &len);
		if (status != 0) {
			free(time);
			free(data);
			lh_antennas_throwsIdamError(status, "lh_antennas_modules_phase_time", object_name, shotNumber);
			return status;
		}
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return status;
}

Longint h_antennas_antenna_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint len = 2;
	//setReturnDataIntScalar(data_block, len, NULL);
	return 0;
}

Longint h_antennas_antenna_module_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint len = 16;
	//setReturnDataIntScalar(data_block, len, NULL);
	return 0;
}



/*void freeDataBlockContents(DATA_BLOCK* data_block) {
    if (data_block) {
        if (data_block->data) {
            free(data_block->data);
            data_block->data = NULL;
        }
        if (data_block->dims) {
            // Normalement les dim[i].dim sont NULL ici car compressed=1 et dim=NULL
            free(data_block->dims);
            data_block->dims = NULL;
        }
        // Si tu avais alloué error_model, etc.
    }
}*/


// #ifdef WEST_STANDALONE_TEST
// int main() {
// 	Longint nodeIndices [2] = {0,0};
// 	Longint shot = 62651;
// 	//DATA_BLOCK* db = NULL;
// 	auto data_block = (DATA_BLOCK*)calloc(1, sizeof(DATA_BLOCK));

// 	for (int i = 0; i < 2; i++) {
// 		//data_block[i].data = NULL;
// 		//data_block[i].data_n = 0;
// 		//data_block[i].data_type = UDA_TYPE_DOUBLE;
// 		nodeIndices[0] = i + 1;	//antenna id 1 or 2
	
// 		lh_antennas_antenna_power(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_antenna_power");
// 		freeDataBlock(data_block);
// 		lh_antennas_antenna_power_time(shot, data_block, nodeIndices);
// 		freeDataBlock(data_block);
// 		printDataBlockPreview(data_block, "lh_antennas_antenna_power_time");
// 		lh_antennas_power_forward(shot, data_block, nodeIndices);
// 		freeDataBlock(data_block);
// 		printDataBlockPreview(data_block, "lh_antennas_power_forward");
// 		freeDataBlock(data_block);
// 		printDataBlockPreview(data_block, "lh_antennas_power_forward_time");
// 		freeDataBlock(data_block);
// 		lh_antennas_power_reflected(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_power_reflected");
// 		freeDataBlock(data_block);
// 		lh_antennas_power_reflected_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_power_reflected_time");
// 		freeDataBlock(data_block);
// 		lh_antennas_reflection_coefficient(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_reflection_coefficient");
// 		freeDataBlock(data_block);
// 		lh_antennas_reflection_coefficient_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_reflection_coefficient_time");
// 		freeDataBlock(data_block);
// 		lh_antennas_position_definition(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_position_definition");
// 		freeDataBlock(data_block);
// 		lh_antennas_pressure_tank(shot, data_block, nodeIndices);
		
// 		printDataBlockPreview(data_block, "lh_antennas_pressure_tank");
// 		freeDataBlock(data_block);
// 		lh_antennas_pressure_tank_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_pressure_tank_time");
// 		freeDataBlock(data_block);
// 		lh_antennas_position_r(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_position_r");
// 		freeDataBlock(data_block);
// 		lh_antennas_position_r_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "lh_antennas_position_r_time");
// 		freeDataBlock(data_block);
// 		//Longint nodeIndices [1] = {1};

// 		for (int j = 0; j < 16; j++) {
// 			nodeIndices[1] = j + 1;
			
// 			lh_antennas_modules_power(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_power");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_power_time(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_power_time");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_power_forward(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_power_forward");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_power_forward_time(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_power_forward_time");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_power_launched(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_power_launched");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_power_launched_time(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_power_launched_time");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_power_reflected(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_power_reflected");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_power_reflected_time(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_power_reflected_time");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_reflection_coefficient(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_reflection_coefficient");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_reflection_coefficient_time(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_reflection_coefficient_time");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_phase(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_phase");
// 			freeDataBlock(data_block);
// 			lh_antennas_modules_phase_time(shot, data_block, nodeIndices);
// 			printDataBlockPreview(data_block, "lh_antennas_modules_phase_time");
// 			freeDataBlock(data_block);
// 		}	
// 	}				
// 	return 0;
// }
// #endif

