#include "west_dyn_data_utilities.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "west_logging.h"

#include "ts_rqparam.h"
#include "west_utilities.h"
#include "tstype_tmp.h"


void SetDynData(DATA_BLOCK* data_block, Longint len, Double* time, Double* data, Longint setTime);

Longint SetNormalizedDynData(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes, char* normalizationAttributes,
		Longint setTime);


Longint SetNormalizedDynamicData(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes, char* normalizationAttributes)
{
	return SetNormalizedDynData(shotNumber, data_block, nodeIndices,
			TOP_collections_parameters, attributes, normalizationAttributes, 0);
}

Longint SetNormalizedDynamicDataTime(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes, char* normalizationAttributes)
{
	return SetNormalizedDynData(shotNumber, data_block, nodeIndices,
			TOP_collections_parameters, attributes, normalizationAttributes, 1);
}

Longint SetNormalizedDynData(Longint shotNumber, DATA_BLOCK* data_block, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes, char* normalizationAttributes, Longint setTime)
{
	Longint len;
	Double* time = NULL;
	Double* data = NULL;

	Longint status = GetDynData(shotNumber, &time, &data, &len, nodeIndices,
			TOP_collections_parameters, attributes);

	UDA_LOG(UDA_LOG_DEBUG, "after calling GetDynData\n");

	if (status != 0) {
		int err = 901;
		UDA_LOG(UDA_LOG_DEBUG, "after calling GetDynData1\n");
		const char* errorMsg = "WEST:ERROR (SetNormalizedDynData): unable to get dynamic data for TOP parameters: ";
		char msg[1000];
		strcpy(msg, errorMsg);
		sprintf(msg, "%s,shot:%ld\n", TOP_collections_parameters, shotNumber);
		//UDA_LOG(UDA_LOG_ERROR, "%s", msg);
		free(time);
		free(data);
		addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
		
		UDA_LOG(UDA_LOG_DEBUG, "after calling GetDynData2\n");
	} else {
		UDA_LOG(UDA_LOG_DEBUG, "Getting normalization factor, if any\n");
		Double normalizationFactor = 1;
		getNormalizationFactor(&normalizationFactor, normalizationAttributes);
		UDA_LOG(UDA_LOG_DEBUG, "Starting data normalization\n");
		multiplyDouble(data, normalizationFactor, len);
		UDA_LOG(UDA_LOG_DEBUG, "End of data normalization, if any\n");
		SetDynData(data_block, len, time, data, setTime);
	}
	UDA_LOG(UDA_LOG_DEBUG, "End of function SetNormalizedDynData()\n");
	free(time);
	free(data);
	return status;
}

Longint GetNormalizedDynamicData(Longint shotNumber, Double** data_time, Double** data, Longint* len, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes, char* normalizationAttributes)
{
	Longint status = GetDynData(shotNumber, data_time, data, len, nodeIndices,
			TOP_collections_parameters, attributes);

	if (status != 0) {
		int err = 901;
		const char* errorMsg = "WEST:ERROR (GetNormalizedDynamicData): unable to get dynamic data for TOP parameters: ";
		char msg[1000];
		strcpy(msg, errorMsg);
		sprintf(msg, "%s,shot:%ld\n", TOP_collections_parameters, shotNumber);
		//UDA_LOG(UDA_LOG_ERROR, "%s", msg);
		addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
	} else {
		UDA_LOG(UDA_LOG_DEBUG, "Getting normalization factor, if any\n");
		Double normalizationFactor = 1;
		getNormalizationFactor(&normalizationFactor, normalizationAttributes);
		UDA_LOG(UDA_LOG_DEBUG, "Starting data normalization\n");
		multiplyDouble(*data, normalizationFactor, *len);
		UDA_LOG(UDA_LOG_DEBUG, "end of data normalization, if any\n");
	}

	return status;
}

Longint GetDynData(Longint shotNumber, Double** data_time, Double** data, Longint* len, Longint* nodeIndices,
		char* TOP_collections_parameters, char* attributes)
{
	UDA_LOG(UDA_LOG_DEBUG, "Entering in GetDynData()...\n");
	Longint collectionsCount;
	getTopCollectionsCount(TOP_collections_parameters, &collectionsCount);

	Longint* extractionsCount;
	extractionsCount = (Longint*)calloc(collectionsCount, sizeof(Longint));

	Longint signalType = 0;
	Longint i;
	char* command = NULL;
	Longint totalExtractions = 0;

	for (i = 0; i < collectionsCount; i++) {

		UDA_LOG(UDA_LOG_DEBUG, "In GetDynData, i: %ld\n", i);

		getCommand(i, &command, TOP_collections_parameters);

		UDA_LOG(UDA_LOG_DEBUG, "Command: %s\n", command);

		char* objectName = NULL;
		getObjectName(&objectName, command);

		Longint nb_extractions = 0;
		Longint occ = 0;

		UDA_LOG(UDA_LOG_DEBUG, "Group of signals ?\n");
		getSignalType(objectName, shotNumber, &signalType);

		if (signalType == 2) {
			getExtractionsCount(objectName, shotNumber, occ, &nb_extractions);
		}

		UDA_LOG(UDA_LOG_DEBUG, "Number of extractions: %ld", nb_extractions);

		extractionsCount[i] = nb_extractions;
		totalExtractions += extractionsCount[i];
		command = NULL;
	}

	UDA_LOG(UDA_LOG_DEBUG, "searching for IDAM index...\n");
	UDA_LOG(UDA_LOG_DEBUG, "attributes : %s\n", attributes);

	Longint requestedIndex = getNumIDAMIndex(attributes, nodeIndices);

	UDA_LOG(UDA_LOG_DEBUG, "Requested index (from UDA call): %ld\n", requestedIndex);

	Longint searchedArray;
	Longint searchedArrayIndex;
	UDA_LOG(UDA_LOG_DEBUG, "searching for the array according to the UDA index\n");
	searchIndices(requestedIndex, extractionsCount, &searchedArray, &searchedArrayIndex);

	char* objectName = NULL;

	UDA_LOG(UDA_LOG_DEBUG, "searchedArrayIndex: %ld\n", searchedArrayIndex);
	UDA_LOG(UDA_LOG_DEBUG, "searchedArray: %ld\n", searchedArray);

	//This patch means that if the signal does not belong to a group, so it can not be aggregate as signals groups
	//Example of an aggregate : tsbase_collect;DMAG:first_group, DMAG:second_group;Double:#0

	if (signalType != 2) {
		searchedArray = 0;
	}


	UDA_LOG(UDA_LOG_DEBUG, "TOP_collections_parameters: %s\n", TOP_collections_parameters);

	Longint status = getCommand(searchedArray, &command, TOP_collections_parameters);

	if (status != 0) {
		int err = 901;
		char errorMsg[1000];
		strcpy(errorMsg, "WEST:ERROR: unable to get command for TOP parameters:");
		sprintf(errorMsg, "%s,shot:%ld\n", TOP_collections_parameters, shotNumber);
		//UDA_LOG(UDA_LOG_ERROR, "%s", errorMsg);
		free(command);
		free(objectName);
		free(extractionsCount);
		addIdamError(UDA_CODE_ERROR_TYPE, errorMsg, err, "");
		return status;
	}

	UDA_LOG(UDA_LOG_DEBUG, "Command: %s\n", command);
	getObjectName(&objectName, command);
	UDA_LOG(UDA_LOG_DEBUG, "Getting object name: %s\n", objectName);

	UDA_LOG(UDA_LOG_DEBUG, "Group of signals ?\n");
	getSignalType(objectName, shotNumber, &signalType);

	if (signalType == 2) { //signal is a group of signals, so we append extraction chars to signal name
		UDA_LOG(UDA_LOG_DEBUG, "Signal belongs to a group of signals\n");
		char result[50];
		addExtractionChars(result, objectName,
				searchedArrayIndex +
				1); //Concatenate signalName avec %(searchedArrayIndex + 1), example: %1, %2, ...
		objectName = strdup(result);
	} else {
		UDA_LOG(UDA_LOG_DEBUG, "Signal does not belong to a group of signals\n");
	}

	Longint rang[2] = { 0, 0 };
	status = readSignal(objectName, shotNumber, 0, rang, data_time, data, len);

	if (status != 0) {
		/*int err = 901;
		UDA_LOG(UDA_LOG_DEBUG, "WEST:ERROR: error reading signal: %s\n", objectName);
		char* errorMsg = "WEST:ERROR (GetDynData): error reading signal";
		char msg[1000];
		sprintf(msg, "%s,objectName:%s,shot:%ld\n,err:%ld", errorMsg, objectName, shotNumber, status);*/
		//UDA_LOG(UDA_LOG_ERROR, "%s", msg);
		//addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
		free(command);
		free(objectName);
		free(extractionsCount);
		return status;
	}

	UDA_LOG(UDA_LOG_DEBUG, "End of reading signal\n");

	UDA_LOG(UDA_LOG_DEBUG, "signal length: %ld\n", *len);

	/*UDA_LOG(UDA_LOG_DEBUG, "%s\n", "First time values...");
		Longint j;
		for (j=0; j <10; j++) {
			UDA_LOG(UDA_LOG_DEBUG, "time : %f\n", *data_time[j]);
		}*/

	if (*len == 0) {
		int err = 901;
		char msg[1000];
		const char* errorMsg = "WEST:ERROR (GetDynData): dynamic data empty";
		sprintf(msg, "%s,objectName:%s,shot:%ld\n", errorMsg, objectName, shotNumber);
		//UDA_LOG(UDA_LOG_ERROR, "%s", msg);
		addIdamError(UDA_CODE_ERROR_TYPE, msg, err, "");
		status = -1;
	} else {
		status = 0;
	}

	free(command);
	free(objectName);
	free(extractionsCount);

	return status;
}

void SetDynamicData(DATA_BLOCK* data_block, Longint len, Double* data_time, Double* data)
{
	SetDynData(data_block, len, data_time, data, 0);
}

void SetDynamicDataTime(DATA_BLOCK* data_block, Longint len, Double* data_time, Double* data)
{
	SetDynData(data_block, len, data_time, data, 1);
}

void SetDynData(DATA_BLOCK* data_block, Longint len, Double* data_time, Double* data, Longint setTime)
{
    // if (!data_block) return;

    // // LIBÉRATION PRÉALABLE OBLIGATOIRE (le point clé !)
    // if (data_block->data) {
    //     free(data_block->data);
    //     data_block->data = NULL;
    // }
    // if (data_block->dims) {
    //     free(data_block->dims);
    //     data_block->dims = NULL;
    // }

    // // Réinitialisation propre
    // initDataBlock(data_block);

    // data_block->rank      = 1;
    // data_block->data_type = UDA_TYPE_DOUBLE;
    // data_block->data_n    = len;

    // Double* source_data = (setTime == 0) ? data : data_time;

    // // Allocation + copie
    // if (len > 0 && source_data) {
    //     data_block->data = (char*)malloc(len * sizeof(Double));
    //     if (!data_block->data) {
    //         //addIdamError(...);
    //         return;
    //     }
    //     memcpy(data_block->data, source_data, len * sizeof(Double));
    // } else {
    //     data_block->data = NULL;
    //     data_block->data_n = 0;
    // }

    // // Dimensions
    // data_block->dims = (DIMS*)malloc(sizeof(DIMS));
    // if (!data_block->dims) {
    //     free(data_block->data);
    //     data_block->data = NULL;
    //     //addIdamError(...);
    //     return;
    // }

    // initDimBlock(&data_block->dims[0]);
    // data_block->dims[0].dim_n        = len;
    // data_block->dims[0].data_type    = UDA_TYPE_UNSIGNED_INT;
    // data_block->dims[0].compressed   = 1;
    // data_block->dims[0].dim          = NULL;
    // data_block->dims[0].dim0         = 0.0;
    // data_block->dims[0].diff         = 1.0;
    // data_block->dims[0].method       = 0;

    // // Optionnel mais propre
    // strcpy(data_block->data_label, "");
    // strcpy(data_block->data_units, "");
    // strcpy(data_block->data_desc,  "");
}

Longint getArcadeSignal(const char* nomsigp, Longint shotNumber, Longint extractionIndex, Double** data_time, Double** data, Longint* len, Double normalizationFactor)
{
	UDA_LOG(UDA_LOG_DEBUG, "Group of signals ?\n");
	char nomsigp_to_extract[50];

	if (extractionIndex > 0) {
		addExtractionChars(nomsigp_to_extract, nomsigp,
				extractionIndex); //Concatenate nomsigp_to_extract with !extractionIndex, example: !1, !2, ...
	}
	else {
		strcpy(nomsigp_to_extract, nomsigp);
		RemoveSpaces(nomsigp_to_extract);
	}
	UDA_LOG(UDA_LOG_DEBUG, "signal: %s\n", nomsigp_to_extract);
	Longint rang[2] = { 0, 0 };
	Longint status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, data_time, data, len);
	UDA_LOG(UDA_LOG_DEBUG, "readSignal status: %ld\n", status);
	if ((status == 0) && (*len != 0))
		multiplyDouble(*data, normalizationFactor, *len);
	UDA_LOG(UDA_LOG_DEBUG, "returning from getArcadeSignal");
	return status;
}

Longint setUDABlockSignalFromArcade(const char* sigName, Longint shotNumber, Longint extractionIndex, DATA_BLOCK* data_block, Longint* nodeIndices, Double normalizationFactor)
{
	Double *data_time = NULL;
	Double *data = NULL;
	Longint len;

	Longint status = getArcadeSignal(sigName, shotNumber, extractionIndex, &data_time, &data, &len, normalizationFactor);

	if (status == 0) 
		SetDynamicData(data_block, len, data_time, data);
	
	free(data_time);
	free(data);

	return status;
}

Longint setUDABlockTimeFromArcade(const char* sigName, Longint shotNumber, Longint extractionIndex, DATA_BLOCK* data_block, Longint* nodeIndices)
{
	Double *data_time = NULL;
	Double *data = NULL;
	Longint len;

	Longint status = getArcadeSignal(sigName, shotNumber, extractionIndex, &data_time, &data, &len, 1);

	if (status == 0) 
		SetDynamicDataTime(data_block, len, data_time, data);

	free(data_time);
	free(data);
	return status;
}

void merge2Signals_according_to_ip_treshold(Double **data, Longint len, Double *data1, Double *data2, Double *ip, Double treshold) {

	Longint i;
	*data = (Double*) malloc(sizeof(Double)*len);
	for (i = 0; i < len; i++) {
		if (ip[i] >= treshold) {
			*(*data + i) = data2[i];
		}
		else {
			*(*data + i) = data1[i];
		}
	}
}

Longint averageArcadeSignal(const char* sigName, Longint shotNumber, Longint extractions[], Longint extractions_length, Double** data_time, Double** averaged_data, Longint* len) {

	Longint i;

	for (i=0; i<extractions_length; i++) {

		Longint status = -1;
		if (i == 0) {
			status = getArcadeSignal(sigName, shotNumber, extractions[i], data_time, averaged_data, len, 1.);
		}
		else {
			Double *data = NULL;
			status = getArcadeSignal(sigName, shotNumber, extractions[i], data_time, &data, len, 1.);
			if (status == 0)
				sum(*averaged_data, data, *len);
		}

		if (status != 0) {
			return status;
		}
	}
	normalize(*averaged_data, *len, extractions_length);
	return 0;
}


void sum(Double* sum_data, Double* data, Longint len) {
	Longint i;
	for (i = 0; i < len; i++) {
		sum_data[i] = data[i] + sum_data[i];
	}
}

void substract(Double* diff_data, Double* data, Longint len) {
	Longint i;
	for (i = 0; i < len; i++) {
		diff_data[i] = diff_data[i] - data[i];
	}
}

void normalize(Double* sum_data, Longint len, Longint normalizationFactor) {
	Longint i;
	for (i = 0; i < len; i++) {
		sum_data[i] = sum_data[i]/normalizationFactor;
	}
}

void multiply(Double* data, Longint len, Double factor) {
	Longint i;
	for (i = 0; i < len; i++) {
		data[i] = data[i]*factor;
	}
}

Longint signalsRatio(Double **result_q_by_r, Double *q, Double *r, Longint lenq, Longint lenr) {
	UDA_LOG(UDA_LOG_DEBUG, "length of q:%ld\n", lenq);
	UDA_LOG(UDA_LOG_DEBUG, "length of r:%ld\n", lenr);
	if (lenq != lenr)
		return -1;
	*result_q_by_r = (Double*) malloc(sizeof(Double)*lenq);
	Longint i;
	for (i = 0; i < lenq; i++) {
		//UDA_LOG(UDA_LOG_DEBUG, "r[i]=%f\n", r[i]);
		if (r[i] < 1e-30)
			*(*result_q_by_r + i) = 0.;
		else
			*(*result_q_by_r + i) = q[i]/r[i];
	}
	return 0;
}

Longint signalsSquare(Double **square_s, Double *s, Longint len) {
	*square_s = (Double*) malloc(sizeof(Double)*len);
	Longint i;
	for (i = 0; i < len; i++)
		*(*square_s + i) = s[i]*s[i];
	return 0;
}

Longint multiplySignals(Double **result, Double *p, Double *q, Longint len) {
	*result = (Double*) malloc(sizeof(Double)*len);
	Longint i;
	for (i = 0; i < len; i++)
		*(*result + i) = p[i]*q[i];
	return 0;
}

Longint equals(Double *p, Double *q, Longint len) {
	Longint i;
	for (i = 0; i < len; i++) {
		if (abs(p[i] - q[i]) > 1.e-8) {
			return 0;
		}
	}
	return 1;
}

/*void setReturnData2DDouble (DATA_BLOCK* data_block, Longint dim1_shape, Longint dim2_shape, Double* data)
{
	//IDAM data block initialization
	initDataBlock(data_block);
	data_block->rank = 2;
	data_block->dims = (DIMS*)malloc(data_block->rank * sizeof(DIMS));

	Longint i;
	for (i = 0; i < data_block->rank; i++) {
		initDimBlock(&data_block->dims[i]);
		data_block->dims[i].data_type = UDA_TYPE_UNSIGNED_INT;
		data_block->dims[i].compressed = 1;
		data_block->dims[i].dim0 = 0.0;
		data_block->dims[i].diff = 1.0;
		data_block->dims[i].method = 0;
	}
	data_block->data_type = UDA_TYPE_DOUBLE;
	data_block->dims[0].dim_n = dim1_shape;
	data_block->dims[1].dim_n = dim2_shape;
	data_block->data_n = dim1_shape*dim2_shape;
	data_block->data = (char*)data;
}*/

void setReturnData2DDouble(DATA_BLOCK* data_block,
                           Longint dim1_shape,
                           Longint dim2_shape,
                           Double* data)   // <-- const + pas de free ici !
{
    // 1. Initialisation obligatoire
    /*initDataBlock(data_block);

    // 2. Métadonnées du tableau 2D
    data_block->rank      = 2;
    data_block->data_type = UDA_TYPE_DOUBLE;
    data_block->data_n    = dim1_shape * dim2_shape;

    // 3. Allocation + copie des données (OBLIGATOIRE !)
    double* buffer = (double*)malloc(data_block->data_n * sizeof(double));
    if (!buffer) {
        //addIdamError(CODE_ERROR_TYPE, "setReturnData2DDouble", 999, "malloc failed for data");
        return;
    }
    memcpy(buffer, data, data_block->data_n * sizeof(double));
    data_block->data = (char*)buffer;

    // 4. Allocation des dimensions (rank = 2)
    data_block->dims = (DIMS*)malloc(2 * sizeof(DIMS));
    if (!data_block->dims) {
        free(buffer);
        data_block->data = NULL;
        //addIdamError(CODE_ERROR_TYPE, "setReturnData2DDouble", 999, "malloc failed for dims");
        return;
    }

    // 5. Initialisation des deux dimensions
    for (int i = 0; i < 2; i++) {
        initDimBlock(&data_block->dims[i]);
        data_block->dims[i].data_type  = UDA_TYPE_UNSIGNED_INT;  // indices
        data_block->dims[i].compressed = 1;
        data_block->dims[i].dim0       = 0.0;
        data_block->dims[i].diff       = 1.0;
        data_block->dims[i].method     = 0;
        data_block->dims[i].dim        = NULL;
    }

    data_block->dims[0].dim_n = dim1_shape;   // ex: nombre de temps
    data_block->dims[1].dim_n = dim2_shape;   // ex: nombre d'antennes
	*/
}

Longint time_field(const char *object_name, Longint shotNumber, Longint extractionIndex, Double **time, Double **data, Longint* len) {
	UDA_LOG(UDA_LOG_DEBUG, "Calling time_field function\n");
	char nomsigp_to_extract[50];
	addExtractionChars(nomsigp_to_extract, object_name, extractionIndex); //Concatenate nomsigp_to_extract avec !extractionIndex, example: !1, !2, ...
	Longint rang[2] = { 0, 0 };
	Longint status = readSignal(nomsigp_to_extract, shotNumber, 0, rang, time, data, len);
	return status;
}

