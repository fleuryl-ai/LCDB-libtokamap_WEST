
#ifndef IDAM_PLUGIN_WEST_LH_ANTENNAS_H
#define IDAM_PLUGIN_WEST_LH_ANTENNAS_H

#include "tstype_tmp.h"

Longint lh_antennas_ids_properties_comment(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_power(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_power_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_antenna_power(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_antenna_power_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_power_forward(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_power_forward_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_power_reflected(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_power_reflected_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_reflection_coefficient(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_reflection_coefficient_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_power(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_power_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_power_forward(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_power_forward_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_power_launched(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_power_launched_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_power_reflected(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_power_reflected_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_reflection_coefficient(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_reflection_coefficient_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_phase(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_modules_phase_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_phase_average(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_phase_average_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_n_parallel_peak(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_n_parallel_peak_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_position_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_position_r_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_position_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_position_definition(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_pressure_tank(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint lh_antennas_pressure_tank_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
void lh_antennas_throwsIdamError(Longint status, const char* methodName, const char * objectName, Longint shotNumber);
void lh_antennas_throwsIdamError2(Longint status, const char* methodName, const char * objectName, Longint shotNumber, Longint antennaId);

#endif // IDAM_PLUGIN_WEST_LH_ANTENNAS_H
