#include "west_summary.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "west_dyn_data_utilities.h"
#include "west_dynamic_data.h"
#include "west_static_data_utilities.h"

void summary_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber) {
	int err = 901;
	char msg[1000];
	sprintf(msg, "%s(%s),object:%s,shot:%ld,err:%ld\n", "WEST:ERROR", methodName, object_name, shotNumber, status);
	//UDA_LOG(UDA_LOG_ERROR, "%s", msg);
	addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
}

Longint summary_global_quantities_v_loop_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Longint extractions [4];
	extractions[0] = 1;
	extractions[1] = 3;
	extractions[2] = 4;
	extractions[3] = 6;
	Double *averaged_data_time = NULL;
	Double* averaged_data = NULL;
	Longint len;
	Longint status = averageArcadeSignal("GMAG_VLOOP", shotNumber, extractions, 4, &averaged_data_time, &averaged_data, &len);

	if (status != 0) {
		free(averaged_data_time);
		free(averaged_data);
		summary_throwsIdamError(status, "summary_global_quantities_v_loop_value", "averageArcadeSignal", shotNumber);
		return status;
	}

	Double *time2 = NULL;
	Double *data2 = NULL;
	Longint len2;

	status = getArcadeSignal("GMAG_FV", shotNumber, 2, &time2, &data2, &len2, 1.0);

	if (status != 0) {
		free(averaged_data_time);
		free(averaged_data);
		free(time2);
		free(data2);
		summary_throwsIdamError(status,"summary_global_quantities_v_loop_value", "GMAG_FV", shotNumber);
		return status;
	}

	Double *ip_time = NULL;
	Double *ip_data = NULL;
	Longint ip_len;

	status = getArcadeSignal("SMAG_IP", shotNumber, 1, &ip_time, &ip_data, &ip_len, 1.0);

	if (status != 0) {
		
		free(averaged_data_time);
		free(averaged_data);
		free(time2);
		free(data2);
		free(ip_time);
		free(ip_data);
		summary_throwsIdamError(status,"summary_global_quantities_v_loop_value", "SMAG_IP", shotNumber);
		return status;
	}

	Double treshold = 10000;

	Double *mergedData = NULL;
	merge2Signals_according_to_ip_treshold(&mergedData, len, averaged_data, data2, ip_data, treshold);
	multiply(mergedData, len, -1.);
	SetDynamicData(data_block, len, averaged_data_time, mergedData);
	free(averaged_data_time);
	free(averaged_data);
	free(time2);
	free(data2);
	free(ip_time);
	free(ip_data);
	free(mergedData);
	return 0;
}

Longint summary_global_quantities_r0_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//setReturnDataDoubleScalar(data_block, 2.42, NULL);
	return 0;
}

Longint summary_global_quantities_beta_tor_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Double *volume_time = NULL;
	Double *volume_data = NULL;
	Longint volume_len;
	const char* volume_sigName = "GMAG_GEOM";
	Longint volume_extractionIndex = 13;

	Longint status = getArcadeSignal(volume_sigName, shotNumber, volume_extractionIndex,
			&volume_time, &volume_data, &volume_len, 1.0);

	if (status != 0) {
		free(volume_time);
		free(volume_data);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_value", "GMAG_GEOM", shotNumber);
		return status;
	}

	Double *total_energy_time = NULL;
	Double *total_energy_data = NULL;
	Longint total_energy_len;
	const char* total_energy_sigName = "GMAG_BILAN";
	Longint total_energy_extractionIndex = 10;

	status = getArcadeSignal(total_energy_sigName, shotNumber, total_energy_extractionIndex,
			&total_energy_time, &total_energy_data, &total_energy_len, 1.0);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_value", "GMAG_BILAN", shotNumber);
		return status;
	}

	UDA_LOG(UDA_LOG_DEBUG, "Getting ratio total_energy_data/volume_data...\n");
	Double *ratio = NULL;
	status = signalsRatio(&ratio, total_energy_data, volume_data, total_energy_len, volume_len);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(ratio);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_value", "get ratio total_energy/volume", shotNumber);
		return status;
	}

	Double *itor_time = NULL;
	Double *itor_data = NULL;
	Longint itor_len;
	const char* itor_sigName = "GMAG_ITOR";
	Longint itor_extractionIndex = 1;

	Double normalizationFactor = 4.*M_PI*1.e-7*18.*2028./(2.*M_PI*2.42);
	UDA_LOG(UDA_LOG_DEBUG, "Getting GMAG_ITOR%1...\n");
	status = getArcadeSignal(itor_sigName, shotNumber, itor_extractionIndex, &itor_time, &itor_data, &itor_len, normalizationFactor);

	if (status != 0) {
		
		free(itor_time);
		free(itor_data);
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(ratio);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_value", "GMAG_ITOR", shotNumber);
		return status;
	}

	UDA_LOG(UDA_LOG_DEBUG, "Getting square of itor_data...\n");
	Double *b0_square = NULL;
	signalsSquare(&b0_square, itor_data, itor_len);

	UDA_LOG(UDA_LOG_DEBUG, "Getting ratio of energy_by_volume by b0_square ...\n");
	Double *energy_by_volume_by_b0_square = NULL;
	status = signalsRatio(&energy_by_volume_by_b0_square, ratio, b0_square, total_energy_len, itor_len);

	if (status != 0) {
		
		free(itor_time);
		free(itor_data);
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(ratio);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_value", "signalsRatio", shotNumber);
		return status;
	}

	Double cste = (2./3.)*2*M_PI*1e-7;

	UDA_LOG(UDA_LOG_DEBUG, "Multiply result with constant ...\n");
	multiply(energy_by_volume_by_b0_square, itor_len, cste);

	SetDynamicData(data_block, itor_len, itor_time, energy_by_volume_by_b0_square);
	free(itor_time);
	free(itor_data);
	free(volume_time);
	free(volume_data);
	free(total_energy_time);
	free(total_energy_data);
	free(ratio);
	free(b0_square);
	free(energy_by_volume_by_b0_square);
	return 0;
}

Longint summary_global_quantities_beta_tor_norm_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	//volume
	//----------------------------------
	Double *volume_time = NULL;
	Double *volume_data = NULL;
	Longint volume_len;
	const char* volume_sigName = "GMAG_GEOM";
	Longint volume_extractionIndex = 13;

	Longint status = getArcadeSignal(volume_sigName, shotNumber, volume_extractionIndex,
			&volume_time, &volume_data, &volume_len, 1.0);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_norm_value", "GMAG_GEOM", shotNumber);
		return status;
	}

	//total energy
	//----------------------------------
	Double *total_energy_time = NULL;
	Double *total_energy_data = NULL;
	Longint total_energy_len;
	const char* total_energy_sigName = "GMAG_BILAN";
	Longint total_energy_extractionIndex = 10;

	status = getArcadeSignal(total_energy_sigName, shotNumber, total_energy_extractionIndex,
			&total_energy_time, &total_energy_data, &total_energy_len, 1.0);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_norm_value", "GMAG_BILAN", shotNumber);
		return status;
	}

	//b0_value
	//----------------------------------
	Double *itor_time = NULL;
	Double *itor_data = NULL;
	Longint itor_len;
	const char* itor_sigName = "GMAG_ITOR";
	Longint itor_extractionIndex = 1;

	Double normalizationFactor = 4.*M_PI*1.e-7*18.*2028./(2.*M_PI*2.42);
	status = getArcadeSignal(itor_sigName, shotNumber, itor_extractionIndex, &itor_time, &itor_data, &itor_len, normalizationFactor);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(itor_time);
		free(itor_data);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_norm_value", "GMAG_ITOR", shotNumber);
		return status;
	}

	const Double treshold = 10000;
	Double *ip_data = NULL;
	Double *ip_time = NULL;
	Longint ip_len;
	status = ip_value(&ip_data, ip_time, &ip_len, shotNumber, data_block, treshold);
	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(itor_time);
		free(itor_data);
		free(ip_data);
		free(ip_time);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_norm_value", "ip_value", shotNumber);
		return status;
	}

	//minor radius
	//----------------------------------
	Double *minor_radius_time = NULL;
	Double *minor_radius_data = NULL;
	Longint minor_radius_len;
	const char* minor_radius_sigName = "GMAG_GEOM";
	Longint minor_radius_extractionIndex = 3;

	status = getArcadeSignal(minor_radius_sigName, shotNumber, minor_radius_extractionIndex,
			&minor_radius_time, &minor_radius_data, &minor_radius_len, 1.0);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(itor_time);
		free(itor_data);
		free(ip_data);
		free(ip_time);
		free(minor_radius_time);
		free(minor_radius_data);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_norm_value", "GMAG_GEOM", shotNumber);
		return status;
	}

	//Total_energy x minor radius
	//----------------------------------
	Double *total_enery_times_minor_radius = NULL;
	multiplySignals(&total_enery_times_minor_radius, total_energy_data, minor_radius_data, total_energy_len);

	//(Total_energy x minor radius)/volume
	//----------------------------------
	Double *total_enery_times_minor_radius_by_volume = NULL;
	status = signalsRatio(&total_enery_times_minor_radius_by_volume, total_enery_times_minor_radius, ip_data, total_energy_len, volume_len);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(itor_time);
		free(itor_data);
		free(ip_data);
		free(ip_time);
		free(minor_radius_time);
		free(minor_radius_data);
		free(total_enery_times_minor_radius_by_volume);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_norm_value", "unable to compute ratio", shotNumber);
		return status;
	}

	//(Total_energy x minor radius)/volume/b0
	//----------------------------------
	Double *total_enery_times_minor_radius_by_volume_by_b0 = NULL;
	status = signalsRatio(&total_enery_times_minor_radius_by_volume_by_b0, total_enery_times_minor_radius_by_volume, itor_data, total_energy_len, itor_len);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(itor_time);
		free(itor_data);
		free(ip_data);
		free(ip_time);
		free(minor_radius_time);
		free(minor_radius_data);
		free(total_enery_times_minor_radius_by_volume);
		free(total_enery_times_minor_radius_by_volume_by_b0);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_norm_value", "unable to compute second ratio", shotNumber);
		return status;
	}

	//(Total_energy x minor radius)/volume/b0/ip
	//----------------------------------
	Double *total_enery_times_minor_radius_by_volume_by_b0_by_ip = NULL;
	status = signalsRatio(&total_enery_times_minor_radius_by_volume_by_b0_by_ip, total_enery_times_minor_radius_by_volume_by_b0, ip_data, total_energy_len, ip_len);

	if (status != 0) {
		
		free(volume_time);
		free(volume_data);
		free(total_energy_time);
		free(total_energy_data);
		free(itor_time);
		free(itor_data);
		free(ip_data);
		free(ip_time);
		free(minor_radius_time);
		free(minor_radius_data);
		free(total_enery_times_minor_radius_by_volume);
		free(total_enery_times_minor_radius_by_volume_by_b0);
		free(total_enery_times_minor_radius_by_volume_by_b0_by_ip);
		summary_throwsIdamError(status,"summary_global_quantities_beta_tor_norm_value", "unable to compute third ratio", shotNumber);
		return status;
	}

	Double cste = 100*1.6*M_PI/3.;
	multiply(total_enery_times_minor_radius_by_volume_by_b0_by_ip, ip_len, cste);
	SetDynamicData(data_block, total_energy_len, ip_time, total_enery_times_minor_radius_by_volume_by_b0_by_ip);
	free(volume_time);
	free(volume_data);
	free(total_energy_time);
	free(total_energy_data);
	free(itor_time);
	free(itor_data);
	free(ip_data);
	free(ip_time);
	free(minor_radius_time);
	free(minor_radius_data);
	free(total_enery_times_minor_radius);
	free(total_enery_times_minor_radius_by_volume);
	free(total_enery_times_minor_radius_by_volume_by_b0);
	free(total_enery_times_minor_radius_by_volume_by_b0_by_ip);
	return 0;
}

Longint summary_global_quantities_b0_value(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Double *itor_time = NULL;
	Double *itor_data = NULL;
	Longint itor_len;
	const char* itor_sigName = "GMAG_ITOR";
	Longint itor_extractionIndex = 1;

	Double normalizationFactor = 4*M_PI*1e-7*18*2028/(2*M_PI*2.42);
	Longint status = getArcadeSignal(itor_sigName, shotNumber, itor_extractionIndex, &itor_time, &itor_data, &itor_len, normalizationFactor);

	if (status != 0) {
		
		free(itor_time);
		free(itor_data);
		summary_throwsIdamError(status,"summary_global_quantities_b0_value", "GMAG_ITOR", shotNumber);
		return status;
	}

	SetDynamicData(data_block, itor_len, itor_time, itor_data);
	free(itor_time);
	free(itor_data);
	return 0;
}

Longint summary_heating_current_drive_ec_power(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Longint k = nodeIndices[0]; //starts from 1
	Longint status = -1;
	if (k == 1) {
		const char* mappingValue = "flt1D;DMAG:GMAG_BILAN:2";
		status = flt1D(mappingValue, shotNumber, data_block, nodeIndices);
	}
	else if (k == 2) {
		const char* mappingValue = "flt1D;DMAG:GMAG_BILAN:3";
		status = flt1D(mappingValue, shotNumber, data_block, nodeIndices);
	}
	else if (k == 3) {
		const char* mappingValue = "flt1D;DMAG:GMAG_BILAN:4";
		status = flt1D(mappingValue, shotNumber, data_block, nodeIndices);
	}
	return status;
}

Longint summary_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {
	//NOT IMPLEMENTED
	return 0;
}

Longint summary_heating_current_drive_ec_power_source(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices) {

	Longint k = nodeIndices[0]; //starts from 1
	if (k == 1) {
		//setReturnDataString(data_block, "LHCD", NULL);
	}
	else if (k == 2) {
		//setReturnDataString(data_block, "ICRH", NULL);
	}
	else if (k == 3) {
		//setReturnDataString(data_block, "ECRH", NULL);
	}
	return 0;
}

Longint ip_value(Double **ip_data, Double *ip_time, Longint *ip_len, Longint shotNumber, DATA_BLOCK* data_block, const Double treshold) {
	//ip value
	//----------------------------------
	Double *ifreeb_time = NULL;
	Double *ifreeb_data = NULL;
	Longint ifreeb_len;
	const char* ifreeb_sigName = "GMAG_IFREEB";
	Longint ifreeb_extractionIndex = 1;

	Double normalizationFactor = 1.0;
	Longint status = getArcadeSignal(ifreeb_sigName, shotNumber, ifreeb_extractionIndex, &ifreeb_time, &ifreeb_data, &ifreeb_len, normalizationFactor);

	if (status != 0) {
		
		free(ifreeb_time);
		free(ifreeb_data);
		summary_throwsIdamError(status,"ip_value", "GMAG_IFREEB", shotNumber);
		return status;
	}

	Double *smagip_time = NULL;
	Double *smagip_data = NULL;
	Longint smagip_len;
	const char* smagip_sigName = "SMAG_IP";
	Longint smagip_extractionIndex = 1;

	normalizationFactor = 1.0;
	status = getArcadeSignal(smagip_sigName, shotNumber, smagip_extractionIndex, &smagip_time, &smagip_data, &smagip_len, normalizationFactor);

	if (status != 0) {
		
		free(smagip_time);
		free(smagip_data);
		free(ifreeb_time);
		free(ifreeb_data);
		summary_throwsIdamError(status,"ip_value", "SMAG_IP", shotNumber);
		return status;
	}
	ip_time = ifreeb_time;
	*ip_len = ifreeb_len;
	merge2Signals_according_to_ip_treshold(ip_data, smagip_len, ifreeb_data, smagip_data, smagip_data, treshold);
	free(ifreeb_data);
	free(smagip_time);
	free(smagip_data);	
	return 0;
}
