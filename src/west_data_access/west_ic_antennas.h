
#ifndef IDAM_PLUGIN_WEST_IC_ANTENNAS_H
#define IDAM_PLUGIN_WEST_IC_ANTENNAS_H

#include "tstype_tmp.h"

Longint ic_antennas_ids_properties_comment(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_power_forward(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_power_forward_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_power_reflected(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_power_reflected_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_phase_forward(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_phase_forward_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_phase_reflected(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_phase_reflected_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_voltage_phase(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_voltage_phase_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_current(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_current_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_voltage(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_voltage_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_matching_element_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_matching_element_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_matching_element_capacity(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_matching_element_capacity_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_pressure_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_pressure_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_pressure(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_module_pressure_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_power_launched(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_power_launched_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_frequency(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_frequency_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_modules_strap_outline_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_modules_strap_outline_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_modules_strap_outline_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_modules_strap_width_tor(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_modules_strap_distance_to_conductor(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_modules_strap_phase_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint ic_antennas_modules_strap_phase_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

#endif // IDAM_PLUGIN_WEST_IC_ANTENNAS_H
