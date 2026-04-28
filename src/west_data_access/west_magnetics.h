
#ifndef IDAM_PLUGIN_WEST_MAGNETICS_H
#define IDAM_PLUGIN_WEST_MAGNETICS_H


#include "tstype_tmp.h"

Longint magnetics_bpol_probe_field_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint magnetics_flux_loop_flux_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint magnetics_method_ip_data_error_upper(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint magnetics_bpol_probe_area(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint magnetics_bpol_probe_length(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint magnetics_bpol_probe_turns(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

struct magnetics_features {
	double radius;
	double Z;
	double pol_angle;
	double effective_area;
	double length;
};

#endif // IDAM_PLUGIN_WEST_MAGNETICS_H
