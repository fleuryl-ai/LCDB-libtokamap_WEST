#include "west_dynamic_data.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"
#include "west_utilities.h"
#include "west_dyn_data_utilities.h"

#include "west_pf_passive.h"
#include "west_pf_active.h"
#include "west_soft_x_rays.h"
#include "west_summary.h"
#include "west_lh_antennas.h"
#include "west_barometry.h"
#include "west_ic_antennas.h"
#include "west_magnetics.h"
#include "west_tf.h"

void freeTokenizedFunParameters(char** unvalid, char** top, char** attr, char** norm)
{
    if (unvalid) free(*unvalid); *unvalid = NULL;
    if (top)     free(*top);     *top = NULL;
    if (attr)    free(*attr);    *attr = NULL;
    if (norm && *norm) { free(*norm); *norm = NULL; }
}

Longint GetDynamicData(Longint shotNumber, const char* mapfun, DATA_BLOCK* data_block, Longint* nodeIndices)
{

	UDA_LOG(UDA_LOG_DEBUG, "Entering GetDynamicData() -- WEST plugin\n");

	assert(mapfun); //Mandatory function to get WEST data

	char* fun_name = NULL; //Shape_of, tsmat_collect, tsbase
	char* TOP_collections_parameters = NULL; //example : TOP_collections_parameters = DMAG:GMAG_BNORM:PosR, DMAG:GMAG_BTANG:PosR, ...
	char* attributes = NULL; //example: attributes = 1:Double:#1 (rank = 1, type = Double, #1 = second IDAM index)
	char* normalizationAttributes = NULL; //example : multiply:cste:3     (multiply value by constant factor equals to 3)

	getFunName(mapfun, &fun_name);

	UDA_LOG(UDA_LOG_DEBUG, "UDA request: %s for shot: %ld\n", fun_name, shotNumber);

	if (strcmp(fun_name, "tsbase_collect") == 0) {
		//UDA_LOG(UDA_LOG_DEBUG, "BAD branching %s for shot: %ld\n", fun_name, shotNumber);
		tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
		Longint r = SetNormalizedDynamicData(shotNumber, data_block, nodeIndices, TOP_collections_parameters, attributes,
				normalizationAttributes);
		freeTokenizedFunParameters(NULL, &TOP_collections_parameters, &attributes, &normalizationAttributes);
		return r;
	} else if (strcmp(fun_name, "tsbase_time") == 0) {
		tokenizeFunParameters(mapfun, &TOP_collections_parameters, &attributes, &normalizationAttributes);
		Longint r = SetNormalizedDynamicDataTime(shotNumber, data_block, nodeIndices, TOP_collections_parameters, attributes,
				normalizationAttributes);
		freeTokenizedFunParameters(NULL, &TOP_collections_parameters, &attributes, &normalizationAttributes);
		return r;
	} else if (strcmp(fun_name, "tsbase_collect_with_channels") == 0) {
		char* unvalid_channels = NULL; //used for interfero_polarimeter IDS, example : invalid_channels:1,2
		tokenizeFunParametersWithChannels(mapfun, &unvalid_channels, &TOP_collections_parameters, &attributes,
				&normalizationAttributes);
		freeTokenizedFunParameters(&unvalid_channels, &TOP_collections_parameters, &attributes, &normalizationAttributes);
		return SetNormalizedDynamicData(shotNumber, data_block, nodeIndices, TOP_collections_parameters, attributes,
				normalizationAttributes);
	} else if (strcmp(fun_name, "tsbase_time_with_channels") == 0) {
		char* unvalid_channels = NULL; //used for interfero_polarimeter IDS, example : invalid_channels:1,2
		tokenizeFunParametersWithChannels(mapfun, &unvalid_channels, &TOP_collections_parameters, &attributes,
				&normalizationAttributes);
		freeTokenizedFunParameters(&unvalid_channels, &TOP_collections_parameters, &attributes, &normalizationAttributes);
		return SetNormalizedDynamicDataTime(shotNumber, data_block, nodeIndices, TOP_collections_parameters, attributes,
				normalizationAttributes);
	} else if (strcmp(fun_name, "pf_passive_current_data") == 0) {
		return pf_passive_current_data(shotNumber, data_block, nodeIndices);
	} else if (strcmp(fun_name, "pf_passive_current_time") == 0) {
		UDA_LOG(UDA_LOG_DEBUG, "-->UDA request pf_passive_current_time for shot: %ld\n", shotNumber);
		Longint st = pf_passive_current_time(shotNumber, data_block, nodeIndices);
		UDA_LOG(UDA_LOG_DEBUG, "-->end of UDA request pf_passive_current_time for shot: %ld, status=%ld\n", shotNumber, st);
		return st;
	} else if (strcmp(fun_name, "pf_active_current_data") == 0) {
		return pf_active_current_data(shotNumber, data_block, nodeIndices);
	} else if (strcmp(fun_name, "pf_active_coil_current_data_error_upper") == 0) {
		return pf_active_coil_current_data_error_upper(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "pf_active_current_time") == 0) {
		return pf_active_current_time(shotNumber, data_block, nodeIndices);
	} else if (strcmp(fun_name, "soft_x_rays_channels_power_density_data") == 0) {
		return soft_x_rays_channels_power_density_data(shotNumber, data_block, nodeIndices); //TODO
	} else if (strcmp(fun_name, "soft_x_rays_time") == 0) {
		return soft_x_rays_time(shotNumber, data_block, nodeIndices); //TODO
	} else if (strcmp(fun_name, "flt1D") == 0) {
		return flt1D(mapfun, shotNumber, data_block, nodeIndices); //TODO
	} else if (strcmp(fun_name, "summary_global_quantities_v_loop_value") == 0) {
		return summary_global_quantities_v_loop_value(shotNumber, data_block, nodeIndices); //TODO
	} else if (strcmp(fun_name, "summary_global_quantities_b0_value") == 0) {
		return summary_global_quantities_b0_value(shotNumber, data_block, nodeIndices); //TODO
	} else if (strcmp(fun_name, "summary_global_quantities_beta_tor_value") == 0) {
		return summary_global_quantities_beta_tor_value(shotNumber, data_block, nodeIndices); //TODO
	} else if (strcmp(fun_name, "summary_heating_current_drive_ec_power") == 0) {
		return summary_heating_current_drive_ec_power(shotNumber, data_block, nodeIndices); //TODO
	} else if (strcmp(fun_name, "summary_time") == 0) {
		return summary_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "lh_antennas_power") == 0) {
		return lh_antennas_power(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_power_time") == 0) {
		return lh_antennas_power_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_antenna_power") == 0) {
		return lh_antennas_antenna_power(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_antenna_power_time") == 0) {
		return lh_antennas_antenna_power_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_power_forward") == 0) {
		return lh_antennas_power_forward(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_power_forward_time") == 0) {
		return lh_antennas_power_forward_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_power_reflected") == 0) {
		return lh_antennas_power_reflected(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_power_reflected_time") == 0) {
		return lh_antennas_power_reflected_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_reflection_coefficient") == 0) {
		return lh_antennas_reflection_coefficient(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_reflection_coefficient_time") == 0) {
		return lh_antennas_reflection_coefficient_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_power") == 0) {
		return lh_antennas_modules_power(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_power_time") == 0) {
		return lh_antennas_modules_power_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_power_forward") == 0) {
		return lh_antennas_modules_power_forward(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_power_forward_time") == 0) {
		return lh_antennas_modules_power_forward_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_power_launched") == 0) {
		return lh_antennas_modules_power_launched(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_power_launched_time") == 0) {
		return lh_antennas_modules_power_launched_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_power_reflected") == 0) {
		return lh_antennas_modules_power_reflected(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_power_reflected_time") == 0) {
		return lh_antennas_modules_power_reflected_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_reflection_coefficient") == 0) {
		return lh_antennas_modules_reflection_coefficient(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_reflection_coefficient_time") == 0) {
		return lh_antennas_modules_reflection_coefficient_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_phase") == 0) {
		return lh_antennas_modules_phase(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_modules_phase_time") == 0) {
		return lh_antennas_modules_phase_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_phase_average") == 0) {
		return lh_antennas_phase_average(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_phase_average_time") == 0) {
		return lh_antennas_phase_average_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_n_parallel_peak") == 0) {
		return lh_antennas_n_parallel_peak(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_n_parallel_peak_time") == 0) {
		return lh_antennas_n_parallel_peak_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_position_r") == 0) {
		return lh_antennas_position_r(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_position_r_time") == 0) {
		return lh_antennas_position_r_time(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_position_z") == 0) {
		return lh_antennas_position_z(shotNumber, data_block, nodeIndices);
	}else if (strcmp(fun_name, "lh_antennas_pressure_tank") == 0) {
		return lh_antennas_pressure_tank(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "lh_antennas_pressure_tank_time") == 0) {
		return lh_antennas_pressure_tank_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "barometry_gauge_pressure_data") == 0) {
		return barometry_gauge_pressure_data(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "barometry_gauge_pressure_time") == 0) {
		return barometry_gauge_pressure_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_power_forward") == 0) {
		return ic_antennas_module_power_forward(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_power_forward_time") == 0) {
		return ic_antennas_module_power_forward_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_power_reflected") == 0) {
		return ic_antennas_module_power_reflected(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_power_reflected_time") == 0) {
		return ic_antennas_module_power_reflected_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_phase_forward") == 0) {
		return ic_antennas_module_phase_forward(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_phase_forward_time") == 0) {
		return ic_antennas_module_phase_forward_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_phase_reflected") == 0) {
		return ic_antennas_module_phase_reflected(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_phase_reflected_time") == 0) {
		return ic_antennas_module_phase_reflected_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_voltage") == 0) {
		return ic_antennas_module_voltage(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_voltage_time") == 0) {
		return ic_antennas_module_voltage_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_voltage_phase") == 0) {
		return ic_antennas_module_voltage_phase(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_voltage_phase_time") == 0) {
		return ic_antennas_module_voltage_phase_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_current") == 0) {
		return ic_antennas_module_current(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_current_time") == 0) {
		return ic_antennas_module_current_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_matching_element_capacity") == 0) {
		return ic_antennas_module_matching_element_capacity(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_matching_element_capacity_time") == 0) {
		return ic_antennas_module_matching_element_capacity_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_pressure") == 0) {
		return ic_antennas_module_pressure(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_module_pressure_time") == 0) {
		return ic_antennas_module_pressure_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_power_launched") == 0) {
		return ic_antennas_power_launched(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_power_launched_time") == 0) {
		return ic_antennas_power_launched_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_modules_strap_phase_data") == 0) {
		return ic_antennas_modules_strap_phase_data(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_modules_strap_phase_time") == 0) {
		return ic_antennas_modules_strap_phase_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_frequency") == 0) {
		return ic_antennas_frequency(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "ic_antennas_frequency_time") == 0) {
		return ic_antennas_frequency_time(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "magnetics_bpol_probe_field_data_error_upper") == 0) {
		return magnetics_bpol_probe_field_data_error_upper(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "magnetics_flux_loop_flux_data_error_upper") == 0) {
		return magnetics_flux_loop_flux_data_error_upper(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "magnetics_method_ip_data_error_upper") == 0) {
		return magnetics_method_ip_data_error_upper(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "tf_b_field_tor_vacuum_r_data_error_upper") == 0) {
		return tf_b_field_tor_vacuum_r_data_error_upper(shotNumber, data_block, nodeIndices); //TODO
	}else if (strcmp(fun_name, "tf_delta_b_field_tor_vacuum_r_data_error_upper") == 0) {
                return tf_delta_b_field_tor_vacuum_r_data_error_upper(shotNumber, data_block, nodeIndices); //TODO
        }
		else if (strcmp(fun_name, "tf_b_field_tor_vacuum_r_data") == 0) {
           return tf_b_field_tor_vacuum_r_data(shotNumber, data_block, nodeIndices); //TODO
		} 
		else if (strcmp(fun_name, "tf_delta_b_field_tor_vacuum_r_data") == 0) {
           return tf_delta_b_field_tor_vacuum_r_data(shotNumber, data_block, nodeIndices); //TODO
		} 
		else if (strcmp(fun_name, "tf_time") == 0) {
           return tf_time(shotNumber, data_block, nodeIndices); //TODO
		} 
         /*else if (strcmp(fun_name, "test_fun") == 0) {
		return test_fun(shotNumber, data_block, nodeIndices); //TODO
	}*/

	else {
		const char* errorMsg = "WEST:ERROR: mapped C function not found in west_dynamic_data.c !\n";
		char msg[1000];
		strcpy(msg, errorMsg);
		sprintf(msg, ",function:%s,shot:%ld\n", fun_name, shotNumber);
		UDA_LOG(UDA_LOG_ERROR,"%s\n", msg);
		UDA_LOG(UDA_LOG_DEBUG,"%s\n", msg);
	}
	free(fun_name);
	/*free(TOP_collections_parameters);
	free(attributes);
	free(normalizationAttributes);*/
	return 0;
}

Longint flt1D(const char* mappingValue, Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	UDA_LOG(UDA_LOG_DEBUG, "Calling flt1D\n");
	char* diagnostic = NULL;
	char* object_name = NULL;
	Longint extractionIndex;
	char* normalizationAttributes = NULL;
	tokenize1DArcadeParameters(mappingValue, &diagnostic, &object_name, &extractionIndex, &normalizationAttributes);
	Double normalizationFactor = 1.0;
	getNormalizationFactor(&normalizationFactor, normalizationAttributes);
	Longint status = setUDABlockSignalFromArcade(object_name, shotNumber, extractionIndex, data_block, nodeIndices, normalizationFactor);
	if (status != 0) {
		int err = 901;
		char errorMsg[1000];
		strcpy(errorMsg, "WEST:ERROR (flt1D): unable to get object:");
		sprintf(errorMsg, "%s,shot:%ld\n", object_name, shotNumber);
		free(diagnostic);
		free(object_name);
		free(normalizationAttributes);
		addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
	}
	free(diagnostic);
	free(object_name);
	free(normalizationAttributes);
	return status;
}
