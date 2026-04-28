
#ifndef IDAM_PLUGIN_WEST_SOFT_X_RAYS_H
#define IDAM_PLUGIN_WEST_SOFT_X_RAYS_H

#include "tstype_tmp.h"

Longint soft_x_rays_idsproperties_comment(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint soft_x_rays_channels_shapeof(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint channel_line_of_sight_first_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint channel_line_of_sight_first_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint channel_line_of_sight_first_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint channel_line_of_sight_second_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint channel_line_of_sight_second_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint channel_line_of_sight_second_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint soft_x_rays_channels_energy_band_shapeof(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint soft_x_rays_channels_energy_band_lower_bound(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint soft_x_rays_channels_energy_band_upper_bound(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint soft_x_rays_channels_power_density_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint soft_x_rays_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

void soft_x_rays_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint index, Longint shotNumber);

void soft_x_rays2_throwsIdamError(Longint status, const char* methodName, const char* object_name, Longint shotNumber);

#endif // IDAM_PLUGIN_WEST_SOFT_X_RAYS_H
