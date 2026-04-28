#include "west_pf_active.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"

//Coils data reported by Philippe Moreau for DPOLO diagnostics - 25/08/2017
// R0, Z0, dR, dZ, Nturn
Double A[5] =  { 0.7380,  0.0000, 0.1350, 1.7500, 195}; //coil 'A'
Double Bh[5] = { 1.1180,  1.7500, 0.0750, 1.1000, 176};
Double Dh[5] = { 2.8850,  1.9200, 0.2700, 0.3500, 95 };
Double Eh[5] = { 3.7700,  1.5230, 0.2900, 0.3750, 96 };
Double Fh[5] = { 4.3750,  0.6370, 0.2900, 0.3750, 96 };
Double Fb[5] = { 4.3750, -0.6370, 0.2900, 0.3750, 96 };
Double Eb[5] = { 3.7700, -1.5230, 0.2900, 0.3750, 96 };
Double Db[5] = { 2.8850, -1.9200, 0.2700, 0.3500, 95 };
Double Bb[5] = { 1.1180, -1.7500, 0.0750, 1.1000, 176};

//Divertor coils data reported by Philippe Moreau for DPOLO diagnostics - 26/09/2017
// R0, Z0, dR, dZ, Nturn
Double Xu1[5] = { 2.0115,  0.7432, 0.0320, 0.0340, 4 }; //Xu1
Double Xu2[5] = { 2.0755,  0.7772, 0.0320, 0.0340, 4 }; //Xu2
Double Xu3[5] = { 2.1665,  0.8058, 0.0320, 0.0340, 4 }; //Xu3
Double Xu4[5] = { 2.2305,  0.8398, 0.0320, 0.0340, 4 }; //Xu4 --> coil 'Divertor_up2_LFS'
Double Xl1[5] = { 2.0115, -0.7403, 0.0320, 0.0340, 4 }; //Xl1
Double Xl2[5] = { 2.0755, -0.7743, 0.0320, 0.0340, 4 }; //Xl2
Double Xl3[5] = { 2.1665, -0.8029, 0.0320, 0.0340, 4 }; //Xl3
Double Xl4[5] = { 2.2305, -0.8369, 0.0320, 0.0340, 4 }; //Xl4 --> coil 'Divertor_bottom2_LFS'

const char* COILS_NAMES[] = { "A", "Bh", "Dh", "Eh", "Fh", "Fb", "Eb", "Db", "Bb",
		"Divertor_top1_HFS", "Divertor_top2_HFS", "Divertor_top1_LFS", "Divertor_top2_LFS",
		"Divertor_bottom1_HFS", "Divertor_bottom2_HFS", "Divertor_bottom1_LFS",
		"Divertor_bottom2_LFS" };

Longint pf_active_current(Longint shotNumber, Longint index, Double **time, Double **data, Longint *len);
Longint get_pf_current(Longint shotNumber, Longint extractionIndex, Double** time, Double** data, Longint* len, Double normalizationFactor);
Longint pf_active(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices, Longint index);


void pf_active_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber) {
	Longint err = 901;
	char msg[1000];
	sprintf(msg, "%s(%s),object:%s,shot:%ld,err:%ld\n", "WEST:ERROR", methodName, object_name, shotNumber, status);
	UDA_LOG(UDA_LOG_ERROR, "WEST::%s", msg);
	addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
}

Longint pf_active_current_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
    Longint index = nodeIndices[0]; //starts from 1
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint status = pf_active_current(shotNumber, index, &time, &data, &len);
	if (status != 0) {
		free(time);
		free(data);
		pf_active_throwsIdamError(status, "pf_active_current_data", "", shotNumber);
		return status;
	}
	SetDynamicData(data_block, len, time, data);
	free(time);
	free(data);
	return 0;
}

Longint pf_active_current(Longint shotNumber, Longint index, Double **time, Double **data, Longint *len)
{
	Longint status = -1;
	if (index <= 9) {
		status = get_pf_current(shotNumber, index, time, data, len, 1000.);
	}
	else if (index == 10 || index == 11) {
		status = get_pf_current(shotNumber, 10, time, data, len, 1000.);
	}
	else if (index == 12 || index == 13) {
		status = get_pf_current(shotNumber, 11, time, data, len, 1000.);
	}
	else if (index == 14 || index == 15) {
		status = get_pf_current(shotNumber, 12, time, data, len, 1000.);
	}
	else if (index == 16 || index == 17) {
		status = get_pf_current(shotNumber, 13, time, data, len, 1000.);
	}
	return status;
}


Longint pf_active_current_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//Longint index = nodeIndices[0]; //starts from 1
	Longint index = 1;
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint status = -1;
	if (index <= 9) {
		status = get_pf_current(shotNumber, index, &time, &data, &len, 1000.);
	}
	else if (index == 10 || index == 11) {
		status = get_pf_current(shotNumber, 10, &time, &data, &len, 1000.);
	}
	else if (index == 12 || index == 13) {
		status = get_pf_current(shotNumber, 11, &time, &data, &len, 1000.);
	}
	else if (index == 14 || index == 15) {
		status = get_pf_current(shotNumber, 12, &time, &data, &len, 1000.);
	}
	else if (index == 16 || index == 17) {
		status = get_pf_current(shotNumber, 13, &time, &data, &len, 1000.);
	}
	else {
		UDA_LOG(UDA_LOG_DEBUG, "wrong index !\n");
		free(time);
		free(data);
		pf_active_throwsIdamError(status, "pf_active_current_time", "wrong index", shotNumber);
		return status;
	}
	if (status != 0) {
		free(time);
		free(data);
		pf_active_throwsIdamError(status, "pf_active_current_time", "get_pf_current", shotNumber);
		return status;
	}
	SetDynamicDataTime(data_block, len, time, data);
	free(time);
	free(data);
	return 0;
}


Longint get_pf_current(Longint shotNumber, Longint extractionIndex, Double** time, Double** data, Longint* len, Double normalizationFactor)
{
	const char* nomsigp = "GPOLO_IMES";
	char nomsigp_to_extract[50];
	addExtractionChars(nomsigp_to_extract, nomsigp, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	Longint rang[2] = { 0, 0 };
	Longint status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, time, data, len);
	if (status == 0)
		multiplyDouble(*data, normalizationFactor, *len);
	return status;
}


Longint pf_active_coil_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint index = nodeIndices[0] - 1; //starts from 0
	//setReturnDataString(data_block, COILS_NAMES[index], NULL);
	return 0;
}

Longint pf_active_coil_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return pf_active_coil_name(shotNumber, data_block, nodeIndices);
}

Longint pf_active_element_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint element_number = nodeIndices[1]; //starts from 1
	char s[100];
	sprintf(s, "%ld", element_number);
	//setReturnDataString(data_block, s, NULL);
	return 0;
}

Longint pf_active_element_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	pf_active_element_name(shotNumber, data_block, nodeIndices);
	return 0;
}

Longint pf_active_elements_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint len = 1;
	//setReturnDataIntScalar(data_block, len, NULL);
	return 0;
}

Longint pf_active_coils_shapeOf(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint len = 17;
	//setReturnDataIntScalar(data_block, len, NULL);
	return 0;
}

Longint pf_active_R(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return pf_active(shotNumber, data_block, nodeIndices, 0);
}

Longint pf_active_Z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return pf_active(shotNumber, data_block, nodeIndices, 1);
}

Longint pf_active_W(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return pf_active(shotNumber, data_block, nodeIndices, 2);
}

Longint pf_active_H(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	return pf_active(shotNumber, data_block, nodeIndices, 3);
}

Longint pf_active_turns(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint coil_number = nodeIndices[0]; //starts from 1
	Double r;
	Longint index = 4;

	if (coil_number == 1) {
		r = (Double)A[index];
	} else if (coil_number == 2) {
		r = (Double)Bh[index];
	} else if (coil_number == 3) {
		r = (Double)Dh[index];
	} else if (coil_number == 4) {
		r = (Double)Eh[index];
	} else if (coil_number == 5) {
		r = (Double)Fh[index];
	} else if (coil_number == 6) {
		r = (Double)Fb[index];
	} else if (coil_number == 7) {
		r = (Double)Eb[index];
	} else if (coil_number == 8) {
		r = (Double)Db[index];
	} else if (coil_number == 9) {
		r = (Double)Bb[index];
	} else if (coil_number == 10) {
		r = (Double)Xu1[index];
	} else if (coil_number == 11) {
		r = (Double)Xu2[index];
	} else if (coil_number == 12) {
		r = (Double)Xu3[index];
	} else if (coil_number == 13) {
		r = (Double)Xu4[index];
	} else if (coil_number == 14) {
		r = (Double)Xl1[index];
	} else if (coil_number == 15) {
		r = (Double)Xl2[index];
	} else if (coil_number == 16) {
		r = (Double)Xl3[index];
	} else if (coil_number == 17) {
		r = (Double)Xl4[index];
	} else {
		Longint status = -1;
		pf_active_throwsIdamError(status, "pf_active", "wrong coil_number index", shotNumber);
		return status;
	}
	//setReturnDataDoubleScalar(data_block, r, NULL);
	return 0;
}

Longint pf_active(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices, Longint index)
{
	Longint coil_number = nodeIndices[0]; //starts from 1
	Double r;

	if (coil_number == 1) {
		r = A[index];
	} else if (coil_number == 2) {
		r = Bh[index];
	} else if (coil_number == 3) {
		r = Dh[index];
	} else if (coil_number == 4) {
		r = Eh[index];
	} else if (coil_number == 5) {
		r = Fh[index];
	} else if (coil_number == 6) {
		r = Fb[index];
	} else if (coil_number == 7) {
		r = Eb[index];
	} else if (coil_number == 8) {
		r = Db[index];
	} else if (coil_number == 9) {
		r = Bb[index];
	} else if (coil_number == 10) {
		r = Xu1[index];
	} else if (coil_number == 11) {
		r = Xu2[index];
	} else if (coil_number == 12) {
		r = Xu3[index];
	} else if (coil_number == 13) {
		r = Xu4[index];
	} else if (coil_number == 14) {
		r = Xl1[index];
	} else if (coil_number == 15) {
		r = Xl2[index];
	} else if (coil_number == 16) {
		r = Xl3[index];
	} else if (coil_number == 17) {
		r = Xl4[index];
	} else {
		Longint status = -1;
		pf_active_throwsIdamError(status, "pf_active", "wrong coil_number index", shotNumber);
		return status;
	}
	//setReturnDataDoubleScalar(data_block, r, NULL);
	return 0;
}

Longint pf_active_coil_current_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	Longint index = nodeIndices[0]; //starts from 1
	Double *time = NULL;
	Double *data = NULL;
	Longint len;
	Longint status = pf_active_current(shotNumber, index, &time, &data, &len);
	if (status != 0) {
		free(time);
		free(data);
		pf_active_throwsIdamError(status, "pf_active_coil_current_data_error_upper", "", shotNumber);
		
		return status;
	}

	Double dataMinValue = 30.;
	Double relative_error;

	if (index == 1) {
		relative_error= 0.025;
	}
	else {
		relative_error= 0.01;
	}

	maxValueOfAbs(data, len, dataMinValue, relative_error);
	SetDynamicData(data_block, len, time, data);
	free(time);
	free(data);
	return 0;
}

// #ifdef WEST_STANDALONE_TEST
// int main() {
// 	Longint nodeIndices [1] = {1};
// 	Longint shot = 62651;
// 	//DATA_BLOCK* db = NULL;
// 	auto data_block = (DATA_BLOCK*)calloc(1, sizeof(DATA_BLOCK));
// 	for (int i = 0; i < 2; i++) {
// 		nodeIndices[0] = i + 1;
// 		pf_active_coil_current_data_error_upper(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_coil_current_data_error_upper");
// 		freeDataBlock(data_block);
// 		/*pf_active_coil_current_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_coil_current_time");
// 		freeDataBlock(data_block);*/
// 		pf_active_current_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_current_time");
// 		freeDataBlock(data_block);
// 		pf_active_current_data(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_current_data");
// 		freeDataBlock(data_block);
// 		pf_active_R(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_R");
// 		freeDataBlock(data_block);
// 		pf_active_Z(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_Z");
// 		freeDataBlock(data_block);
// 		pf_active_W(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_W");
// 		freeDataBlock(data_block);
// 		pf_active_H(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_H");
// 		freeDataBlock(data_block);
// 		pf_active_turns(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "pf_active_turns");
// 		freeDataBlock(data_block);	
// 	}	

// 	return 0;
// }
// #endif