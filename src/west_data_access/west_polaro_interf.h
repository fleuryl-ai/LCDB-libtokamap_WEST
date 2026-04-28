#ifndef IDAM_PLUGIN_WEST_POLARO_INTERF_H
#define IDAM_PLUGIN_WEST_POLARO_INTERF_H

#include <stdint.h> // <-- AJOUTEZ CECI pour s'assurer que les types de base sont là
#include "tstype_tmp.h" // <-- Gardez-le décommenté si c'est la source de Longint

Longint interferometer_channel_line_of_sight_first_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polaro_or_interfero_channel_name(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_identifier(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint polarimeter_channel_line_of_sight_first_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_line_of_sight_first_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_line_of_sight_first_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_line_of_sight_second_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_line_of_sight_second_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_line_of_sight_second_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_line_of_sight_third_point_r(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_line_of_sight_third_point_z(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_line_of_sight_third_point_phi(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint polarimeter_channel_faraday_angle_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint polarimeter_channel_faraday_angle_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint interferometer_channel_n_e_line_data(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint interferometer_channel_n_e_line_time(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);


#endif // IDAM_PLUGIN_WEST_POLARO_INTERF_H