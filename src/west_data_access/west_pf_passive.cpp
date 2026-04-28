#include "west_pf_passive.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"

Double Rsup[10] = { 2.3475, 2.3476, 2.3273, 2.3272, 2.3273, 2.3284, 2.3671, 2.3669, 2.3676, 2.3683 };
Double Zsup[10] = { 0.8923, 0.8503, 0.9055, 0.8806, 0.8620, 0.8360, 0.9038, 0.8838, 0.8618, 0.8372 };

Double Rbaf[8] = { 2.6003, 2.6491, 2.5278, 2.5735, 2.6235, 2.6723, 2.6235, 2.6241 };
Double Zbaf[8] = { -0.8503, -0.8503, -0.7216, -0.7222, -0.7222, -0.7222, -0.8094, -0.7618 };

Double Rsup1[3] = { 1.9578, 1.9300, 1.9003 };
Double Zsup1[3] = { 0.7558, 0.7300, 0.6807 };

Double Rsup2[3] = { 2.0678, 2.1521, 2.2167 };
Double Zsup2[3] = { 0.7273, 0.7596, 0.7905 };

Double Rsup3[2] = { 2.2874, 2.2865 };
Double Zsup3[2] = { 0.8451, 0.8883 };

Double Rinf1[3] = { 1.9578, 1.9300, 1.9003 };
Double Zinf1[3] = { -0.7558, -0.7300, -0.6807 };

Double Rinf2[3] = { 2.0678, 2.1521, 2.2167 };
Double Zinf2[3] = { -0.7273, -0.7596, -0.7905 };

Double Rinf3[2] = { 2.2874, 2.2865 };
Double Zinf3[2] = { -0.8451, -0.8883 };

Longint getIFREEB(Longint shotNumber, Longint extractionIndex, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint getIDCOEF(Longint shotNumber, Longint extractionIndex, Double** time, Double** data, Longint* len, Double normalizationFactor);

Longint I_case_upper(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint I_case_lower(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint I_baffle(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint I_uper_stab(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint Ip_fw(Longint shotNumber, Double** time, Double** data, int* len, Double normalizationFactor);
Longint I_case_upper_hfs(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint I_case_upper_c(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint I_case_upper_lfs(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint I_case_lower_hfs(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint I_case_lower_c(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint I_case_lower_lfs(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint getCurrent(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices, Double** data, Double** time, Longint* len);
Double somme(Double* data, Longint len);
void somme2(Double* s, Double* data1, Double* data2, Double* data3, Longint len);
Longint factUpper(Longint shotNumber, Double* result);
Longint factLower(Longint shotNumber, Double* result);

Longint passive_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint passive_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint passive_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint passive_current_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint passive_current(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint passive_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

void pf_passive_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber) {
	int err = 901;
	char msg[1000];
	sprintf(msg, "%s(%s),object:%s,shot:%ld,err:%ld\n", "WEST:ERROR", methodName, object_name, shotNumber, status);
	UDA_LOG(UDA_LOG_ERROR, "%s", msg);
	addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
}

Longint pf_passive_current_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return passive_current(shotNumber, data_block, nodeIndices);
}

Longint pf_passive_current_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return passive_time(shotNumber, data_block, nodeIndices);
}

Longint pf_passive_loop_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return passive_name(shotNumber, data_block, nodeIndices);
}

Longint pf_passive_loop_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return pf_passive_loop_name(shotNumber, data_block, nodeIndices);
}

Longint pf_passive_element_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint element_number = 1;
	char s[100];
	sprintf(s, "%ld", element_number);
	//setReturnDataString(data_block, s, NULL);
	return 0;
}

Longint pf_passive_element_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return pf_passive_element_name(shotNumber, data_block, nodeIndices);
}

Longint pf_passive_elements_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) //TODO
{
	Longint len = 1;
	//setReturnDataIntScalar(data_block, len, NULL);
	return 0;
}

Longint pf_passive_loops_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) //TODO
{
	Longint len = 34;
	//setReturnDataIntScalar(data_block, len, NULL);
	return 0;
}

Longint pf_passive_R(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return passive_r(shotNumber, data_block, nodeIndices);
}

Longint pf_passive_Z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return passive_z(shotNumber, data_block, nodeIndices);
}

Longint pf_passive_turns(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 1, NULL);
	return 0;
}



Longint passive_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint k = nodeIndices[0]; //starts from 1
	char s[100];

	if (k <= 10) {
		sprintf(s, "Upper stabilizing plate (loop %ld)", k);
	} else if (k > 10 && k <= 18) {
		sprintf(s, "Baffle support (loop %ld)", k - 10);
	} else if (k > 18 && k <= 21) {
		sprintf(s, "Upper divertor casing, high field side part (loop %ld)", k - 18);
	} else if (k > 21 && k <= 24) {
		sprintf(s, "Upper divertor casing, centre part (loop %ld)", k - 21);
	} else if (k > 24 && k <= 26) {
		sprintf(s, "Upper divertor casing, low field side part (loop %ld)", k - 24);
	} else if (k > 26 && k <= 29) {
		sprintf(s, "Upper divertor casing, high field side part (loop %ld)", k - 26);
	} else if (k > 29 && k <= 32) {
		sprintf(s, "Lower divertor casing, centre part (loop %ld)", k - 29);
	} else if (k > 32 && k <= 34) {
		sprintf(s, "Lower divertor casing, low field side part (loop %ld)", k - 32);
	} else {
		Longint status = -1;
		pf_passive_throwsIdamError(status,"passive_name", "wrong k index", shotNumber);
		return status;
	}

	//setReturnDataString(data_block, s, NULL);
	return 0;
}

Longint passive_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint k = nodeIndices[0]; //starts from 1
	Double* r = NULL;
	r = (Double*)malloc(sizeof(Double));

	if (k <= 10) {
		r[0] = Rsup[k - 1];
		//printf("DEBUG: passive_r: k=%ld, r=%f\n", k, r[0]);
	} else if (k > 10 && k <= 18) {
		r[0] = Rbaf[k - 11];
	} else if (k > 18 && k <= 21) {
		r[0] = Rsup1[k - 19];
	} else if (k > 21 && k <= 24) {
		r[0] = Rsup2[k - 22];
	} else if (k > 24 && k <= 26) {
		r[0] = Rsup3[k - 25];
	} else if (k > 26 && k <= 29) {
		r[0] = Rinf1[k - 27];
	} else if (k > 29 && k <= 32) {
		r[0] = Rinf2[k - 30];
	} else if (k > 32 && k <= 34) {
		r[0] = Rinf3[k - 33];
	} else {
		Longint status = -1;
		pf_passive_throwsIdamError(status, "passive_r", "wrong k index", shotNumber);
		return status;
	}
	SetStatic1DData(data_block, 1, r);
	free(r);
	return 0;
}

Longint passive_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint k = nodeIndices[0]; //starts from 1
	Double* z = NULL;
	z = (Double*)malloc(sizeof(Double));

	if (k <= 10) {
		z[0] = Zsup[k - 1];
	} else if (k > 10 && k <= 18) {
		z[0] = Zbaf[k - 11];
	} else if (k > 18 && k <= 21) {
		z[0] = Zsup1[k - 19];
	} else if (k > 21 && k <= 24) {
		z[0] = Zsup2[k - 22];
	} else if (k > 24 && k <= 26) {
		z[0] = Zsup3[k - 25];
	} else if (k > 26 && k <= 29) {
		z[0] = Zinf1[k - 27];
	} else if (k > 29 && k <= 32) {
		z[0] = Zinf2[k - 30];
	} else if (k > 32 && k <= 34) {
		z[0] = Zinf3[k - 33];
	} else {
		Longint status = -1;
		pf_passive_throwsIdamError(status, "passive_z", "wrong k index", shotNumber);
		return status;
	}
	SetStatic1DData(data_block, 1, z);
	free(z);
	return 0;
}

Longint passive_current_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint len = 34;
	//setReturnDataIntScalar(data_block, len, NULL);
	return 0;
}

Longint passive_current(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{

	Double* data = NULL;
	Double* time = NULL;
	Longint len;
	Longint status = getCurrent(shotNumber, data_block, nodeIndices, &data, &time, &len);
	if (status != 0) {
		free(data);
		free(time);
		pf_passive_throwsIdamError(status, "passive_current", "", shotNumber);
		
		return status;
	}
	SetDynamicData(data_block, len, time, data);
	free(data);
	free(time);
	return 0;
}

Longint getCurrent(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices, Double** data, Double** time, Longint* len)
{

	Longint k = nodeIndices[0]; //starts from 1
	Longint status = -1;
	const Longint Rsup_length = (Longint)(sizeof(Rsup) / sizeof(Rsup[0]));
	const Longint Rbaf_length = (Longint)(sizeof(Rbaf) / sizeof(Rbaf[0]));
	const Longint Rsup1_length = (Longint)(sizeof(Rsup1) / sizeof(Rsup1[0]));
	const Longint Rsup2_length = (Longint)(sizeof(Rsup2) / sizeof(Rsup2[0]));
	const Longint Rsup3_length = (Longint)(sizeof(Rsup3) / sizeof(Rsup3[0]));
	const Longint Rinf1_length = (Longint)(sizeof(Rinf1) / sizeof(Rinf1[0]));
	const Longint Rinf2_length = (Longint)(sizeof(Rinf2) / sizeof(Rinf2[0]));
	const Longint Rinf3_length = (Longint)(sizeof(Rinf3) / sizeof(Rinf3[0]));

	if (k <= 10) {
		status = I_uper_stab(shotNumber, time, data, len, 1. / Rsup_length);
	} else if (k > 10 && k <= 18) {
		status = I_baffle(shotNumber, time, data, len, 1. / Rbaf_length);
	} else if (k > 18 && k <= 21) {
		status = I_case_upper_hfs(shotNumber, time, data, len, 1. / Rsup1_length);
	} else if (k > 21 && k <= 24) {
		status = I_case_upper_c(shotNumber, time, data, len, 1. / Rsup2_length);
	} else if (k > 24 && k <= 26) {
		status = I_case_upper_lfs(shotNumber, time, data, len, 1. / Rsup3_length);
	} else if (k > 26 && k <= 29) {
		status = I_case_lower_hfs(shotNumber, time, data, len, 1. / Rinf1_length);
	} else if (k > 29 && k <= 32) {
		status = I_case_lower_c(shotNumber, time, data, len, 1. / Rinf2_length);
	} else if (k > 32 && k <= 34) {
		status = I_case_lower_lfs(shotNumber, time, data, len, 1. / Rinf3_length);
	}

	return status;
}


Longint passive_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//Longint k = nodeIndices[0]; //starts from 1
	UDA_LOG(UDA_LOG_DEBUG, "%s", "executing passive_time operation\n");
	Longint k = 1; //IDS is time homogeneous
	Longint len = 0;
	Double* data = NULL;
	Double* time = NULL;
	Longint status = -1;

	if (k <= 10) {
		status = getIFREEB(shotNumber, 2, &time, &data, &len, 1.);
	} else if (k > 10 && k <= 18) {
		status = getIFREEB(shotNumber, 3, &time, &data, &len, 1.);
	} else if (k > 18 && k <= 21) {
		status = getIDCOEF(shotNumber, 19, &time, &data, &len, 1.);
	} else if (k > 21 && k <= 24) {
		status = getIDCOEF(shotNumber, 20, &time, &data, &len, 1.);
	} else if (k > 24 && k <= 26) {
		status = getIDCOEF(shotNumber, 21, &time, &data, &len, 1.);
	} else if (k > 26 && k <= 29) {
		status = getIDCOEF(shotNumber, 22, &time, &data, &len, 1.);
	} else if (k > 29 && k <= 32) {
		status = getIDCOEF(shotNumber, 23, &time, &data, &len, 1.);
	} else if (k > 32 && k <= 34) {
		status = getIDCOEF(shotNumber, 24, &time, &data, &len, 1.);
	}
	UDA_LOG(UDA_LOG_DEBUG, "passive_time status=%ld\n", status);
	if (status != 0) {
		free(data);
		free(time);
		pf_passive_throwsIdamError(status, "passive_current", "", shotNumber);
		return status;
	}
	UDA_LOG(UDA_LOG_DEBUG, "%s", "executing passive_time1\n");
	Double* data_ref = NULL;
	Double* time_ref = NULL;

	status = getIFREEB(shotNumber, 2, &time_ref, &data_ref, &len, 1.);

	if (status != 0) {
		free(data);
		free(time);
		free(data_ref);
		free(time_ref);
		pf_passive_throwsIdamError(status, "passive_current", "", shotNumber);
		return status;
	}
	UDA_LOG(UDA_LOG_DEBUG, "%s", "executing passive_time2\n");
	Longint i;
	const Double p = 1.e-9;
	for (i = 0; i < len ; i++) {
		Double time_ref_i = time_ref[i];
		Double time_i = time[i];
		if (abs(time_ref_i - time_i) > p)  {
			int err = 901;
			char errorMsg[1000];
			strcpy(errorMsg, "WEST:ERROR (passive_time): time data for pf_passive currents differ");
			sprintf(errorMsg, ",shot:%ld", shotNumber);
			//UDA_LOG(UDA_LOG_ERROR, "%s\n", errorMsg);
			free(data);
			free(time);
			free(data_ref);
			free(time_ref);
			addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
			
			return -1;
		}
	}
	UDA_LOG(UDA_LOG_DEBUG, "%s", "executing passive_time3\n");
	SetDynamicDataTime(data_block, len, time, data);
	UDA_LOG(UDA_LOG_DEBUG, "%s", "executing passive_time4\n");
	free(data);
	free(time);
	free(data_ref);
	free(time_ref);
	return 0;
}


Longint getIFREEB(Longint shotNumber, Longint extractionIndex, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	//char* nomsigp = "GMAG_IFREEB";
	char nomsigp[50];
	strcpy(nomsigp, "GMAG_IFREEB");
	char nomsigp_to_extract[100];
	//addExtractionChars(nomsigp_to_extract, nomsigp,
	//		extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	strcpy(nomsigp_to_extract, "GMAG_IFREEB!2");
	Longint rang[2] = { 0, 0 };
	UDA_LOG(UDA_LOG_DEBUG, "getIFREEB, calling readSignal...\n");
	Longint status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, time, data, len);
	UDA_LOG(UDA_LOG_DEBUG, "getIFREEB, readSignal status=%ld\n", status);
	if (status == 0)
		multiplyDouble(*data, normalizationFactor, *len);
	UDA_LOG(UDA_LOG_DEBUG, "getIFREEB, status=%ld\n", status);	
	return status;
}

Longint getIDCOEF(Longint shotNumber, Longint extractionIndex, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	const char* nomsigp = "GMAG_IDCOEF";
	char nomsigp_to_extract[50];
	addExtractionChars(nomsigp_to_extract, nomsigp,
			extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	Longint rang[2] = { 0, 0 };
	Longint status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, time, data, len);
	if (status == 0)
		multiplyDouble(*data, normalizationFactor, *len);
	return status;
}

Longint I_case_upper(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	return getIFREEB(shotNumber, 4, time, data, len, normalizationFactor);
}

Longint I_case_lower(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	return getIFREEB(shotNumber, 5, time, data, len, normalizationFactor);
}

Longint I_baffle(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	return getIFREEB(shotNumber, 3, time, data, len, normalizationFactor);
}

Longint I_uper_stab(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	return getIFREEB(shotNumber, 2, time, data, len, normalizationFactor);
}

Longint Ip_fw(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	return getIFREEB(shotNumber, 1, time, data, len, normalizationFactor);
}

Longint factUpper(Longint shotNumber, Double* result)
{
	Longint I_case_upper_len;
	Double* I_case_upper_data = NULL;
	Double* I_case_upper_time = NULL;
	Longint status = I_case_upper(shotNumber, &I_case_upper_time, &I_case_upper_data, &I_case_upper_len, 1.);
	if (status != 0) {
		free(I_case_upper_data);
		free(I_case_upper_time);
		pf_passive_throwsIdamError(status, "factUpper,I_case_upper", "", shotNumber);
		
		return status;
	}

	Longint coeff_len;
	Double* coeff1_data = NULL;
	Double* coeff1_time = NULL;
	status = getIDCOEF(shotNumber, 19, &coeff1_time, &coeff1_data, &coeff_len, 1.);
	if (status != 0) {
		free(I_case_upper_data);
		free(I_case_upper_time);
		free(coeff1_data);
		free(coeff1_time);
		pf_passive_throwsIdamError(status, "factUpper,getIDCOEF(19)", "", shotNumber);
		
		return status;
	}
	Double* coeff2_data = NULL;
	Double* coeff2_time = NULL;
	status = getIDCOEF(shotNumber, 20, &coeff2_time, &coeff2_data, &coeff_len, 1.);
	if (status != 0) {
		free(I_case_upper_data);
		free(I_case_upper_time);
		free(coeff1_data);
		free(coeff1_time);
		free(coeff2_data);
		free(coeff2_time);
		pf_passive_throwsIdamError(status, "factUpper,getIDCOEF(20)", "", shotNumber);
		
		return status;
	}
	Double* coeff3_data = NULL;
	Double* coeff3_time = NULL;
	status = getIDCOEF(shotNumber, 21, &coeff3_time, &coeff3_data, &coeff_len, 1.);
	if (status != 0) {
		free(I_case_upper_data);
		free(I_case_upper_time);
		free(coeff1_data);
		free(coeff1_time);
		free(coeff2_data);
		free(coeff2_time);
		free(coeff3_data);
		free(coeff3_time);
		pf_passive_throwsIdamError(status, "factUpper,getIDCOEF(21)", "", shotNumber);
		
		return status;
	}

	Double* s2 = NULL;
	s2 = (Double*)calloc(coeff_len, sizeof(Double));
	somme2(s2, coeff1_data, coeff2_data, coeff3_data, coeff_len);
	Double factUpper = somme(I_case_upper_data, I_case_upper_len) / somme(s2, coeff_len);
	*result = factUpper;
	free(I_case_upper_data);
	free(I_case_upper_time);
	free(coeff1_data);
	free(coeff1_time);
	free(coeff2_data);
	free(coeff2_time);
	free(coeff3_data);
	free(coeff3_time);
	free(s2);
	return 0;
}

Longint factLower(Longint shotNumber, Double* result)
{
	Longint I_case_lower_len;
	Double* I_case_lower_data = NULL;
	Double* I_case_lower_time = NULL;
	Longint status = I_case_lower(shotNumber, &I_case_lower_time, &I_case_lower_data, &I_case_lower_len, 1.);
	if (status != 0) {
		
		free(I_case_lower_data);
		free(I_case_lower_time);
		pf_passive_throwsIdamError(status, "factLower,I_case_lower", "", shotNumber);
		return status;
	}

	Longint coeff_len;
	Double* coeff1_data = NULL;
	Double* coeff1_time = NULL;
	status = getIDCOEF(shotNumber, 22, &coeff1_time, &coeff1_data, &coeff_len, 1.);
	if (status != 0) {
		
		free(I_case_lower_data);
		free(I_case_lower_time);
		free(coeff1_data);
		free(coeff1_time);
		pf_passive_throwsIdamError(status, "factLower,getIDCOEF(22)", "", shotNumber);
		return status;
	}

	Double* coeff2_data = NULL;
	Double* coeff2_time = NULL;
	status = getIDCOEF(shotNumber, 23, &coeff2_time, &coeff2_data, &coeff_len, 1.);
	if (status != 0) {
		
		free(I_case_lower_data);
		free(I_case_lower_time);
		free(coeff1_data);
		free(coeff1_time);
		free(coeff2_data);
		free(coeff2_time);
		pf_passive_throwsIdamError(status, "factLower,getIDCOEF(23)", "", shotNumber);
		return status;
	}

	Double* coeff3_data = NULL;
	Double* coeff3_time = NULL;
	status = getIDCOEF(shotNumber, 24, &coeff3_time, &coeff3_data, &coeff_len, 1.);
	if (status != 0) {
		
		free(I_case_lower_data);
		free(I_case_lower_time);
		free(coeff1_data);
		free(coeff1_time);
		free(coeff2_data);
		free(coeff2_time);
		free(coeff3_data);
		free(coeff3_time);
		pf_passive_throwsIdamError(status, "factLower,getIDCOEF(24)", "", shotNumber);
		return status;
	}

	Double* s2 = NULL;
	s2 = (Double*)calloc(coeff_len, sizeof(Double));
	somme2(s2, coeff1_data, coeff2_data, coeff3_data, coeff_len);

	Double factLower = somme(I_case_lower_data, I_case_lower_len) / somme(s2, coeff_len);
	*result = factLower;
	free(I_case_lower_data);
	free(I_case_lower_time);
	free(coeff1_data);
	free(coeff1_time);
	free(coeff2_data);
	free(coeff2_time);
	free(coeff3_data);
	free(coeff3_time);
	free(s2);
	return status;;
}

Longint I_case_upper_hfs(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	Double fu = 0;
	Longint status = factUpper(shotNumber, &fu);
	if (status != 0)
		return status;
	return getIDCOEF(shotNumber, 19, time, data, len, fu*normalizationFactor);
}

Longint I_case_upper_c(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	Double fu = 0;
	Longint status = factUpper(shotNumber, &fu);
	if (status != 0)
		return status;
	return getIDCOEF(shotNumber, 20, time, data, len, fu*normalizationFactor);
}

Longint I_case_upper_lfs(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	Double fu = 0;
	Longint status = factUpper(shotNumber, &fu);
	if (status != 0)
		return status;
	return getIDCOEF(shotNumber, 21, time, data, len, fu*normalizationFactor);
}

Longint I_case_lower_hfs(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	Double fl = 0;
	Longint status = factLower(shotNumber, &fl);
	if (status != 0)
		return status;
	return getIDCOEF(shotNumber, 22, time, data, len, fl*normalizationFactor);
}

Longint I_case_lower_c(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	Double fl = 0;
	Longint status = factLower(shotNumber, &fl);
	if (status != 0)
		return status;
	return getIDCOEF(shotNumber, 23, time, data, len, fl*normalizationFactor);
}

Longint I_case_lower_lfs(Longint shotNumber, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	Double fl = 0;
	Longint status = factLower(shotNumber, &fl);
	if (status != 0)
		return status;
	return getIDCOEF(shotNumber, 24, time, data, len, fl*normalizationFactor);
}

Double somme(Double* data, Longint len)
{
	Longint i;
	Double s = 0;
	for (i = 0; i < len; i++) {
		s += data[i];
	}
	return s;
}

void somme2(Double* s, Double* data1, Double* data2, Double* data3, Longint len)
{
	Longint i;
	for (i = 0; i < len; i++) {
		s[i] = data1[i] + data2[i] + data3[i];
	}
}


// #ifdef WEST_STANDALONE_TEST
// int main() {
// 	Longint nodeIndices [1] = {1};
// 	Longint shot = 62651;
// 	//DATA_BLOCK* db = NULL;
// 	auto data_block = (DATA_BLOCK*)calloc(1, sizeof(DATA_BLOCK));
// 	for (int i = 0; i < 2; i++) {
// 		nodeIndices[0] = i + 1;
		
// 		pf_passive_loop_name(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_passive_loop_name");
// 		freeDataBlock(data_block);
// 		pf_passive_R(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_passive_R");
// 		freeDataBlock(data_block);
// 		pf_passive_Z(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_passive_Z");
// 		freeDataBlock(data_block);
// 		pf_passive_current_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_passive_current_time");
// 		freeDataBlock(data_block);
// 		pf_passive_current_data(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_passive_current_data");
// 		freeDataBlock(data_block);
// 	}	

// 	return 0;
// }
// #endif

