#ifndef IDAM_PLUGIN_WEST_DYNAMIC_DATA_H
#define IDAM_PLUGIN_WEST_DYNAMIC_DATA_H

//#include <libxml/xpath.h>


#include "tstype_tmp.h"

Longint GetDynamicData(Longint shotNumber, const char* mapfun, DATA_BLOCK* data_block, Longint* nodeIndices);
Longint flt1D(const char* mappingValue, Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices);

#endif // IDAM_PLUGIN_WEST_DYNAMIC_DATA_H
