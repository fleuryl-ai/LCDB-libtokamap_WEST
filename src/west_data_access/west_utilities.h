#ifndef IDAM_PLUGIN_WEST_UTILITIES_H
#define IDAM_PLUGIN_WEST_UTILITIES_H

#include <math.h>
//#include <libxml/xpath.h>

#include "tstype_tmp.h"

void tokenize1DArcadeParameters(const char* s, char** diagnostic, char** object_name, Longint* extractionIndex, char** normalizationAttributes);
void tokenize1DArcadeParameters2(const char* s, char** diagnostic, char** object_name, Longint* extractionIndex, char** diagnostic2, char** object_name2, Longint* extractionIndex2);
void RemoveSpaces(char* source);
void getValueCollect(char* command, char** value, Longint* nodeIndices);
void multiplyDouble(Double* p, Double factor, Longint val_nb);
void multiplyInt(Longint* p, Double factor, Longint val_nb);
void maxValueOfAbs(Double* v, Longint val_nb, Double mincst, Double relative_error);

void getFunName(const char* s, char** fun_name);
Longint getNormalizationFactor(Double* normalizationFactor, char* normalizationAttributes);
void setValue(Longint data_type, DATA_BLOCK* data_block, char* value, Longint requestedIndex, Double normalizationFactor);
void set1DValue(Longint data_type, DATA_BLOCK* data_block, char* value, Longint val_nb, Double normalizationFactor);
void setINTValue(Longint data_type, DATA_BLOCK* data_block, Longint value, Double normalizationFactor);
void getRank(char* attributes, Longint* rank);
void tokenizeFunParameters(const char* s, char** argument_name, char** attributes, char** normalizationAttributes);
void tokenizeFunParametersWithChannels(const char* s, char** unvalid_channels, char** TOP_collections_parameters,
		char** attributes, char** normalizationAttributes);
void tokenize_set_channels_validity(const char* s, char** unvalid_channels, char** attributes);
void tokenizeCommand(const char* s, char** prod_name, char** obj_name, char** param_name, char **flag);
Longint  getCommand(Longint i, char** command, const char* TOP_collections_parameters);
void getUnvalidChannelsSize(char* unvalid_channels, Longint* size);
void getUnvalidChannels(char* unvalid_channels, Longint* v);
Longint  isChannelValid(Longint channel_number, Longint* unvalid_channels_list, Longint unvalid_channels_list_size);

Longint  getNumIDAMIndex(char* attributes, Longint* nodeIndices);
Longint  getNumIDAMIndex2(char* s, Longint* nodeIndices);

Longint getReturnType(char* attributes, Longint* dataType);
void searchIndices(Longint requestedIndex, Longint* l, Longint* searchedArray, Longint* searchedArrayIndex);
void addExtractionChars(char* result, const char* signalName, Longint extractionIndex);
void getTopCollectionsCount(const char* TOP_collections_parameters, Longint* collectionsCount);
void getObjectName(char** obj_name, char* command);

void printDataBlockPreview(DATA_BLOCK* db, const char* signal_name = "signal");

Longint execute_setvalue_collect(const char* TOP_collections_parameters, char* attributes,
		Longint shotNumber, Longint* nodeIndices, char* normalizationAttributes);


#endif // IDAM_PLUGIN_WEST_UTILITIES_H
