#include "west_soft_x_rays.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "ts_rqparam.h"
#include "west_static_data_utilities.h"

const int CHANNELS_COUNT = 45;
const int GTXMH1_CHANNELS_COUNT = 28;

Double second_point_z[45] =  {-654.80,-623.10,-591.70,-560.50,-529.60,-498.90,-468.50,
		-438.30,-408.20,-378.30,-348.60,-319.10,-289.60,-260.30,-231.10,-202.00,-173.00,
		-144.10,-115.20,-86.30,-57.50,-28.80, 0.00,28.80,57.50,86.30,115.20,144.10,173.00,
		202.00,231.10,260.30,289.60,319.10,348.60,378.30,408.20,438.30,468.50,498.90,529.60,
		560.50,591.70,623.10,654.80};

Longint channels_power_density(Longint shotNumber, const char* nomsigp, Longint extractionIndex, Double** time, Double** data, Longint* len);
void apply_calibration( Double* calibrated_data, Double* data, Double Cx, Double Ce, Double E, Longint len);

void soft_x_rays_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint index, Longint shotNumber) {
	int err = 901;
	char msg[1000];
	sprintf(msg, "%s(%s),object:%s,index:%ld,shot:%ld,err:%ld\n", "WEST:ERROR", methodName, object_name, index, shotNumber, status);
	addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
}

void soft_x_rays2_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber) {
	int err = 901;
	char msg[1000];
	sprintf(msg, "%s(%s),object:%s,shot:%ld,err:%ld\n", "WEST:ERROR", methodName, object_name, shotNumber,status);
	addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
}

Longint soft_x_rays_idsproperties_comment(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	const char* comment = "WEST soft-X-rays diagnostic (September 2017), experimental data. Horizontal camera only, with old (Tore Supra) detectors.";
	//setReturnDataString(data_block, comment, NULL);
	return 0;
}

Longint soft_x_rays_channels_shapeof(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataIntScalar(data_block, CHANNELS_COUNT, NULL);
	return 0;
}

Longint channel_line_of_sight_first_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 4.3458, NULL);
	return 0;
}

Longint channel_line_of_sight_first_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 0., NULL);
	return 0;
}

Longint channel_line_of_sight_first_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 1.396, NULL);
	return 0;
}

Longint channel_line_of_sight_second_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 2.4, NULL);
	return 0;
}

Longint channel_line_of_sight_second_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint index = nodeIndices[0] - 1; //starts from 0
	//setReturnDataDoubleScalar(data_block, second_point_z[index]*1e-3, NULL);
	return 0;
}

Longint channel_line_of_sight_second_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 1.396, NULL);
	return 0;
}

Longint soft_x_rays_channels_energy_band_shapeof(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataIntScalar(data_block, 1, NULL);
	return 0;
}

Longint soft_x_rays_channels_energy_band_lower_bound(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 1500, NULL);
	return 0;
}

Longint soft_x_rays_channels_energy_band_upper_bound(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 15000, NULL);
	return 0;
}

Longint soft_x_rays_channels_power_density_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint index = nodeIndices[0]; //starts from 1

	Longint len;
	Double *time = NULL;
	Double *data = NULL;
	char* nomsigp = NULL;

	Longint extractionIndex;

	if (index <= GTXMH1_CHANNELS_COUNT) {
		nomsigp = strdup("GTXMH1");
		extractionIndex = index;
	}
	else {
		nomsigp = strdup("GTXMH2");
		extractionIndex = index - GTXMH1_CHANNELS_COUNT;
	}
	UDA_LOG(UDA_LOG_DEBUG, "reading channels_power_density...\n");
	Longint status = channels_power_density(shotNumber, nomsigp, extractionIndex, &time, &data, &len);

	if (status != 0) {
		free(time);
		free(data);
		UDA_LOG(UDA_LOG_DEBUG, "reading channels_power_density, error status...\n");
		soft_x_rays_throwsIdamError(status, "soft_x_rays_channels_power_density_data", nomsigp, extractionIndex, shotNumber);
		return status;
	}

	UDA_LOG(UDA_LOG_DEBUG, "setting file pointer...\n");
	FILE* p_file_soft_x_rays_calib_ce_cx_e;
	Double* Ce = (Double*) malloc(CHANNELS_COUNT*sizeof(Double));
	Double* Cx = (Double*) malloc(CHANNELS_COUNT*sizeof(Double));
	Double* E =  (Double*) malloc(CHANNELS_COUNT*sizeof(Double));

	UDA_LOG(UDA_LOG_DEBUG, "reading WEST_SOFT_X_RAYS_CALIB_CE_CX_E_FILE...\n");
	char* soft_x_rays_calib_ce_cx_e_file = getenv("WEST_SOFT_X_RAYS_CALIB_CE_CX_E_FILE");
	p_file_soft_x_rays_calib_ce_cx_e = fopen(soft_x_rays_calib_ce_cx_e_file, "r");

	if (p_file_soft_x_rays_calib_ce_cx_e == NULL) {
		free(time);
		free(data);
		free(Ce);
		free(Cx);
		free(E);
		soft_x_rays2_throwsIdamError(status, "readCalibrationFile", "unable to read soft_x_rays calibration file", shotNumber);
		return -1;
	} else {
		Longint i = 0;
		for(i = 0; i < CHANNELS_COUNT; i++)
		{
			fscanf(p_file_soft_x_rays_calib_ce_cx_e,"%e",&Ce[i]);
			UDA_LOG(UDA_LOG_DEBUG, "Ce[%d] = %e\n", i, Ce[i]);
			fscanf(p_file_soft_x_rays_calib_ce_cx_e,"%e",&Cx[i]);
			UDA_LOG(UDA_LOG_DEBUG, "Cx[%d] = %e\n", i, Cx[i]);
			fscanf(p_file_soft_x_rays_calib_ce_cx_e,"%e",&E[i]);
			UDA_LOG(UDA_LOG_DEBUG, "E[%d] = %e\n", i, E[i]);
		}

		UDA_LOG(UDA_LOG_DEBUG, "closing file\n");
		fclose(p_file_soft_x_rays_calib_ce_cx_e);
	}
	UDA_LOG(UDA_LOG_DEBUG, "allocation of calibrated_data\n");
	Double *calibrated_data = (Double*) malloc(len*sizeof(Double));
	UDA_LOG(UDA_LOG_DEBUG, "applying calibration coefficients\n");
	apply_calibration(calibrated_data, data, Cx[index - 1], Ce[index - 1], E[index - 1], len);
	UDA_LOG(UDA_LOG_DEBUG, "after applying calibration coefficients\n");
	UDA_LOG(UDA_LOG_DEBUG, "setting channels_power_density...\n");
	setReturnData2DDouble(data_block, 1, len, calibrated_data);
	free(time);
	free(data);
	free(Ce);
	free(Cx);
	free(E);
	return 0;
}

Longint soft_x_rays_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint index = nodeIndices[0]; //starts from 1

	Longint len;
	Double *time = NULL;
	Double *data = NULL;
	const char* nomsigp = strdup("GTXMH1");

	Longint extractionIndex = 1; //IDS is time homogeneous, so we take the first column for the time

	//This function has ambiguous name, however it returns also the time, not only the power density
	Longint status = channels_power_density(shotNumber, nomsigp, extractionIndex, &time, &data, &len);

	if (status != 0) {
		free(time);
		free(data);
		soft_x_rays_throwsIdamError(status, "soft_x_rays_time", nomsigp, extractionIndex, shotNumber);
		return status;
	}
	else {
		SetDynamicDataTime(data_block, len, time, data);
		free(time);
		free(data);
		return status;
	}
}

Longint channels_power_density(Longint shotNumber, const char* nomsigp, Longint extractionIndex, Double** time, Double** data, Longint* len)
{
	char nomsigp_to_extract[50];
	addExtractionChars(nomsigp_to_extract, nomsigp, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	Longint rang[2] = { 0, 0 };
	Longint status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, time, data, len);
	UDA_LOG(UDA_LOG_DEBUG, "end of reading channels_power_density signal !...\n");
	return status;
}

void apply_calibration( Double* calibrated_data, Double* data, Double Cx, Double Ce, Double E, Longint len) {
	Double Ri = 3.76;
	Double Ga = 4;
	Double Gr = 250997;
	Double C = 6553.6;
	Longint i;
	for (i = 0; i < len; i++) {
		calibrated_data[i] = data[i]*Ri*Cx*Ce/Ga/Gr/C/E;
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
// 		soft_x_rays_channels_power_density_data(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "soft_x_rays_channels_power_density_data");
// 		freeDataBlock(data_block);
// 		soft_x_rays_time(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "soft_x_rays_time");
// 		freeDataBlock(data_block);
// 		soft_x_rays_idsproperties_comment(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "soft_x_rays_idsproperties_comment");
// 		freeDataBlock(data_block);
// 		soft_x_rays_channels_shapeof(shot, data_block, nodeIndices);
// 		printDataBlockPreview(data_block, "soft_x_rays_channels_shapeof");
// 		freeDataBlock(data_block);
		
// 	}	

// 	return 0;
// }
// #endif