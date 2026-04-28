#include "west_magnetics.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"

void magnetics_throwsError(Longint status, const char* methodName, Longint shotNumber);
Longint readFile (const char* fileName, Longint shotNumber,
		struct magnetics_features *mag_f, Longint rowindex, Longint skipPolAngle);

Longint magnetics_bpol_probe_field_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	const char* mapfun = "tsbase_collect;DMAG:GMAG_BNORM,DMAG:GMAG_BTANG,DMAG:GMAG_BTORO1,DMAG:GMAG_BTORO2;1:Double:#0";
	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetDynData(shotNumber, &time, &data, &len, nodeIndices, TOP_collections_parameters, attributes);
	if (status != 0) {
		magnetics_throwsError(status, "magnetics_bpol_probe_field_data_error_upper", shotNumber);
		return status;
	}
	Double dataMinValue = 0.001;
	Double relative_error= 0.01;
	maxValueOfAbs(data, len, dataMinValue, relative_error);

	//Longint status = SetNormalizedDynamicData(shotNumber, data_block, nodeIndices, TOP_collections_parameters, attributes,
	//				normalizationAttributes);

	SetDynamicData(data_block, len, time, data);
	free(time);
	free(data);	
	free(fun_name);
	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);
	return 0;
}

Longint magnetics_flux_loop_flux_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	const char* mapfun = "tsbase_collect;DMAG:GMAG_FLXLOOP;1:Double:#0";
	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetDynData(shotNumber, &time, &data, &len, nodeIndices, TOP_collections_parameters, attributes);
	if (status != 0) {
		free(time);
		free(data);	
		free(fun_name);
		free(TOP_collections_parameters);
		free(attributes);
		free(normalizationAttributes);
		magnetics_throwsError(status, "magnetics_flux_loop_flux_data_error_upper", shotNumber);
		return status;
	}
	Double dataMinValue = 0.01;
	Double relative_error= 0.01;
	maxValueOfAbs(data, len, dataMinValue, relative_error);

	SetDynamicData(data_block, len, time, data);
	free(time);
	free(data);	
	free(fun_name);
	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);
	return 0;
}

Longint magnetics_method_ip_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	const char* mapfun = "flt1D;DMAG:SMAG_IP:0;multiply:cste:1000";
	tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);

	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetNormalizedDynamicData(shotNumber, &time, &data,
			&len, nodeIndices, TOP_collections_parameters, attributes, normalizationAttributes);
	if (status != 0) {
		free(time);
		free(data);	
		free(fun_name);
		free(TOP_collections_parameters);
		free(attributes);
		free(normalizationAttributes);
		magnetics_throwsError(status, "magnetics_method_ip_data_error_upper", shotNumber);
		return status;
	}
	Double dataMinValue = 5000;
	Double relative_error = 0.02;
	maxValueOfAbs(data, len, dataMinValue, relative_error);

	SetDynamicData(data_block, len, time, data);
	free(time);
	free(data);	
	free(fun_name);
	free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);
	return 0;
}

Longint magnetics_bpol_probe_area(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint status = -1;
	Longint magnetID = nodeIndices[0]; //starts from 1
	magnetID--; //starts now from 0
	char* UDA_WEST_MAGNETICS_GMAG_BNORM = getenv("UDA_WEST_MAGNETICS_GMAG_BNORM");
	char* UDA_WEST_MAGNETICS_GMAG_BTANG = getenv("UDA_WEST_MAGNETICS_GMAG_BTANG");
	char* UDA_WEST_MAGNETICS_GMAG_BTORO1 = getenv("UDA_WEST_MAGNETICS_GMAG_BTORO1");
	char* UDA_WEST_MAGNETICS_GMAG_BTORO2 = getenv("UDA_WEST_MAGNETICS_GMAG_BTORO2");
	if (magnetID < 55) {
		struct magnetics_features gmag_bnorm;
		status = readFile(UDA_WEST_MAGNETICS_GMAG_BNORM, shotNumber, &gmag_bnorm, magnetID, 0);
		//setReturnDataDoubleScalar(data_block, gmag_bnorm.effective_area, NULL);
	} else if (magnetID >=55 && magnetID < 110) {
		struct magnetics_features gmag_btang;
		status = readFile(UDA_WEST_MAGNETICS_GMAG_BTANG, shotNumber, &gmag_btang, magnetID - 55, 0);
		//setReturnDataDoubleScalar(data_block, gmag_btang.effective_area, NULL);
	} else if (magnetID >=110 && magnetID < 120) {
		struct magnetics_features gmag_btoro1;
		status = readFile(UDA_WEST_MAGNETICS_GMAG_BTORO1, shotNumber, &gmag_btoro1, magnetID - 110, 1);
		//setReturnDataDoubleScalar(data_block, gmag_btoro1.effective_area, NULL);
	} else {
		struct magnetics_features gmag_btoro2;
		status = readFile(UDA_WEST_MAGNETICS_GMAG_BTORO2, shotNumber, &gmag_btoro2, magnetID - 120, 1);
		//setReturnDataDoubleScalar(data_block, gmag_btoro2.effective_area, NULL);
	}
	status = 0;
	return status;
}

Longint magnetics_bpol_probe_length(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint status = -1;
	Longint magnetID = nodeIndices[0]; //starts from 1
	magnetID--; //starts now from 0
	char* UDA_WEST_MAGNETICS_GMAG_BNORM = getenv("UDA_WEST_MAGNETICS_GMAG_BNORM");
	char* UDA_WEST_MAGNETICS_GMAG_BTANG = getenv("UDA_WEST_MAGNETICS_GMAG_BTANG");
	char* UDA_WEST_MAGNETICS_GMAG_BTORO1 = getenv("UDA_WEST_MAGNETICS_GMAG_BTORO1");
	char* UDA_WEST_MAGNETICS_GMAG_BTORO2 = getenv("UDA_WEST_MAGNETICS_GMAG_BTORO2");
	if (magnetID < 55) {
		struct magnetics_features gmag_bnorm;
		status = readFile(UDA_WEST_MAGNETICS_GMAG_BNORM, shotNumber, &gmag_bnorm, magnetID, 0);
		//setReturnDataDoubleScalar(data_block, gmag_bnorm.length, NULL);
	} else if (magnetID >=55 && magnetID < 110) {
		struct magnetics_features gmag_btang;
		status = readFile(UDA_WEST_MAGNETICS_GMAG_BTANG, shotNumber, &gmag_btang, magnetID - 55, 0);
		//setReturnDataDoubleScalar(data_block, gmag_btang.length, NULL);
	} else if (magnetID >=110 && magnetID < 120) {
		struct magnetics_features gmag_btoro1;
		status = readFile(UDA_WEST_MAGNETICS_GMAG_BTORO1, shotNumber, &gmag_btoro1, magnetID - 110, 1);
		//setReturnDataDoubleScalar(data_block, gmag_btoro1.length, NULL);
	} else {
		struct magnetics_features gmag_btoro2;
		status = readFile(UDA_WEST_MAGNETICS_GMAG_BTORO2, shotNumber, &gmag_btoro2, magnetID - 120, 1);
		//setReturnDataDoubleScalar(data_block, gmag_btoro2.length, NULL);
	}
	status = 0;
	return status;
}

Longint magnetics_bpol_probe_turns(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	//setReturnDataIntScalar(data_block, 1, NULL);
	return 0;
}

void magnetics_throwsError(Longint status, const char* methodName, Longint shotNumber) {
	Longint err = 901;
	char errorMsg[1000];
	sprintf(errorMsg, "%s(%s),shot:%ld,err:%ld\n", "WEST:ERROR", methodName, shotNumber,status);
	addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
}

Longint readFile (const char* fileName, Longint shotNumber,
		struct magnetics_features *mag_f, Longint rowindex, Longint skipPolAngle)
{
	FILE* fic ;
	char row[200];
	char *data_ptr;
	short int row_num = 0 ;

	//----------------------- opening CSV file ------------------------------
	fic = fopen( fileName, "rt") ;
	if (fic==NULL)
	{
		return -1;
	}
	//----------------------- reading CSV data------------------------------

	while ( fgets( row, 200, fic) != NULL )
	{
		if (rowindex == row_num) {
			data_ptr = strtok (row, ";");
			sscanf(data_ptr, "%lf", &mag_f->radius);
			data_ptr = strtok (NULL, ";");
			sscanf(data_ptr, "%lf", &mag_f->Z);
			if (skipPolAngle == 0) {
				data_ptr = strtok (NULL, ";");
				sscanf(data_ptr, "%lf", &mag_f->pol_angle);
			}
			data_ptr = strtok (NULL, ";");
			sscanf(data_ptr, "%lf", &mag_f->effective_area);
			data_ptr = strtok (NULL, ";");
			sscanf(data_ptr, "%lf", &mag_f->length);
			data_ptr = strtok (NULL, ";");
			break;
		}
		row_num++ ;
	}
	fclose(fic);
	return 0;
}
