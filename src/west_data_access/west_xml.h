#ifndef IDAM_PLUGIN_WEST_XML_H
#define IDAM_PLUGIN_WEST_XML_H

//#include <libxml/xpath.h>
//
#include "tstype_tmp.h"

Longint GetStaticData(Longint shotNumber, const char* mapfun, DATA_BLOCK* data_block, Longint* nodeIndices);

Longint execute_tsmat_collect(const char* TOP_collections_parameters, char* attributes,
		Longint shotNumber, Longint* nodeIndices,
		char* normalizationAttributes);

Longint execute_setvalue_collect(const char* TOP_collections_parameters, char* attributes,
		Longint shotNumber, Longint* nodeIndices, char* normalizationAttributes);
#endif // IDAM_PLUGIN_WEST_XML_H
