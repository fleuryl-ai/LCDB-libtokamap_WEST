#include "west_static_data_utilities.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "west_logging.h"

#include "west_utilities.h"
#include "ts_rqparam.h"


/*Longint setUDABlockFromArcadeScalarField(Longint data_type, char* prod_name, char* object_name, char* param_name, Longint index,
		Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices, Double normalizationFactor)
{
	Longint nb_val;
	char* value = NULL;
	Longint val_nb = 1;
	Longint status = tsrqparm(&value, &nb_val, shotNumber, prod_name, object_name, param_name, val_nb);
	setStaticValue(data_type, data_block, value, index, normalizationFactor);
	return status;
}*/

//Cast the results returned by tsmat according to the type of the data and set IDAM data
void setStaticValue(Longint data_type, DATA_BLOCK* data_block, char* value, Longint requestedIndex, Double normalizationFactor)
{
	UDA_LOG(UDA_LOG_DEBUG, "Entering setStaticValue()\n");
	UDA_LOG(UDA_LOG_DEBUG, "requested index: %ld", requestedIndex);
	assert(value != NULL);
	if (data_type == UDA_TYPE_FLOAT) {
		UDA_LOG(UDA_LOG_DEBUG, "handling float in setStaticValue()\n");
		float* pt_float = (float*)value;
		/*printf("requested index: %ld\n", requestedIndex);
		printf("normalizationFactor: %f\n", normalizationFactor);
		printf("pt_float @index: %f\n", pt_float[requestedIndex]);*/
		//setReturnDataFloatScalar(data_block, pt_float[requestedIndex] * (float)normalizationFactor, NULL);

	} else if (data_type == UDA_TYPE_DOUBLE) {
		UDA_LOG(UDA_LOG_DEBUG, "handling Double in setStaticValue(): %ld, %g\n", requestedIndex, normalizationFactor);
		Double* pt_Double = (Double*)value;
		UDA_LOG(UDA_LOG_DEBUG, "in setStaticValue(), requestedIndex:  %ld\n", requestedIndex);
		UDA_LOG(UDA_LOG_DEBUG, "in setStaticValue(), normalizationFactor:  %f\n", normalizationFactor);
		UDA_LOG(UDA_LOG_DEBUG, "in setStaticValue(), pt_Double[requestedIndex]:  %f\n", pt_Double[requestedIndex]);
		UDA_LOG(UDA_LOG_DEBUG, "Doubleing value set to  %f\n", pt_Double[requestedIndex] * normalizationFactor);
		//setReturnDataDoubleScalar(data_block, pt_Double[requestedIndex] * normalizationFactor, NULL);

	} else if (data_type == UDA_TYPE_LONG) {
		UDA_LOG(UDA_LOG_DEBUG, "handling long in setStaticValue()\n");
		long* pt_long = (long*)value;
		//setReturnDataLongScalar(data_block, pt_long[requestedIndex] * (long)normalizationFactor, NULL);

	} else if (data_type == UDA_TYPE_INT) {
		UDA_LOG(UDA_LOG_DEBUG, "handling Longint in setStaticValue()\n");
		int* pt_int = (int*)value;
		UDA_LOG(UDA_LOG_DEBUG, "handling in setStaticValue(): %ld\n", *pt_int);
		//setReturnDataIntScalar(data_block, pt_int[requestedIndex] * (int)normalizationFactor, NULL);

	} else if (data_type == UDA_TYPE_SHORT) {
		UDA_LOG(UDA_LOG_DEBUG, "handling short in setStaticValue()\n");
		Longint* pt_short = (Longint*)value;
		//setReturnDataShortScalar(data_block, pt_short[requestedIndex] * (short)normalizationFactor, NULL);

	} else if (data_type == UDA_TYPE_STRING) {
		UDA_LOG(UDA_LOG_DEBUG, "handling string in setStaticValue()\n");
		//setReturnDataString(data_block, strdup(value), NULL);

	} else {
		int err = 901;
		UDA_LOG(UDA_LOG_DEBUG, "Unsupported data type from setStaticValue()\n");
		//UDA_LOG(UDA_LOG_ERROR, "%s", "WEST:ERROR: unsupported data type");
		addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: unsupported data type", err, "");
	}
}

//TODO, this patch will be removed soon
void set_BTANG_StaticValue(Longint data_type, DATA_BLOCK* data_block, char* value, Longint requestedIndex, Double normalizationFactor)
{
	UDA_LOG(UDA_LOG_DEBUG, "Entering set_BTANG_StaticValue()\n");
	UDA_LOG(UDA_LOG_DEBUG, "requested index: %ld", requestedIndex);
	if (data_type == UDA_TYPE_DOUBLE) {
		UDA_LOG(UDA_LOG_DEBUG, "handling Double in set_BTANG_StaticValue(): %ld, %g\n", requestedIndex, normalizationFactor);
		Double* pt_Double = (Double*)value;

		pt_Double[requestedIndex] = pt_Double[requestedIndex] + 180.;
		if (pt_Double[requestedIndex] >= 360.)
			pt_Double[requestedIndex] = pt_Double[requestedIndex] - 360.;

		//setReturnDataDoubleScalar(data_block, pt_Double[requestedIndex] * normalizationFactor, NULL);

	} else {
		int err = 901;
		UDA_LOG(UDA_LOG_DEBUG, "Unsupported data type from set_BTANG_StaticValue()\n");
		//UDA_LOG(UDA_LOG_ERROR, "%s", "WEST:ERROR: unsupported data type");
		addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: unsupported data type", err, "");
	}
}

void SetStatic1DData(DATA_BLOCK* data_block, Longint len, Double* data)
{
    /*initDataBlock(data_block);

    data_block->rank      = 1;
    data_block->data_type = UDA_TYPE_DOUBLE;
    data_block->data_n    = len;

    // Copie profonde → safe + pas de fuite
    if (len > 0 && data) {
        data_block->data = (char*)malloc(len * sizeof(Double));
        if (data_block->data) {
            memcpy(data_block->data, data, len * sizeof(Double));
        }
    } else {
        data_block->data = NULL;
    }

    // dims
    if (data_block->dims) free(data_block->dims);
    data_block->dims = (DIMS*)malloc(sizeof(DIMS));
    if (data_block->dims) {
        initDimBlock(&data_block->dims[0]);
        data_block->dims[0].dim_n = len;
        data_block->dims[0].data_type = UDA_TYPE_UNSIGNED_INT;
        data_block->dims[0].compressed = 1;
        data_block->dims[0].dim = NULL;
        data_block->dims[0].dim0 = 0.0;
        data_block->dims[0].diff = 1.0;
        data_block->dims[0].method = 0;
    }

    strcpy(data_block->data_label, "");
    strcpy(data_block->data_units, "");
    strcpy(data_block->data_desc,  "");
	*/
}


