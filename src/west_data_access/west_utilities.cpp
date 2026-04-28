#include "west_utilities.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <west_logging.h>

// Codes de format TSLib (utilisés dans ts_rqparm.cpp)
#define OCTET 1
#define STRING12 2
#define INT16 3
#define INT32 4
#define REEL16 5
#define REEL32 6


using Longint = int;
Longint tsrqparm(char** pt_char_address, Longint* nb_val, Longint num_choc, const char* nom_prod, const char* nom_objet, const char* nom_param, Longint val_nb, int *format);

Longint getShapeOf(const char* command, Longint shotNumber, Longint* nb_val, Longint option);
char* setBuffer(Longint data_type, const char* value);


void getFunName(const char* s, char** fun_name)
{
	const char delim[] = ";";
	char* s_copy = strdup(s);
	*fun_name = strdup(strtok(s_copy, delim));
	RemoveSpaces(*fun_name);
	free(s_copy);
}

void tokenize1DArcadeParameters(const char* s, char** diagnostic, char** object_name, Longint* extractionIndex, char** normalizationAttributes)
{
	const char delim[] = ";";
	const char delim2[] = ":";
	char* s_copy = strdup(s);
	
	// Initialiser la tokenisation pour ignorer le premier token (nom de la fonction)
	strtok(s_copy, delim);
	
	// Extraire les tokens suivants
	*diagnostic = strdup(strtok(NULL, delim2));
	RemoveSpaces(*diagnostic);
	*object_name = strdup(strtok(NULL, delim2));
	RemoveSpaces(*object_name);
	char* token = strtok(NULL, delim2); // Note: pas de strdup ici
	if (token != NULL) {
		*extractionIndex = atoi(token);
	}

	// Extraire le dernier token (attributes)
	token = strtok(NULL, delim);
	if (token != NULL) {
		*normalizationAttributes = strdup(token);
		RemoveSpaces(*normalizationAttributes);
	}
	
	free(s_copy);
}

void tokenize1DArcadeParameters2(const char* s, char** diagnostic, char** object_name, Longint* extractionIndex, char** diagnostic2, char** object_name2, Longint* extractionIndex2)
{
	const char delim[] = ";";
	const char delim2[] = ":";
	char* s_copy = strdup(s);
	char* tmp = strdup(strtok(s_copy, delim)); //function name
	*diagnostic = strdup(strtok(NULL, delim2));
	UDA_LOG(UDA_LOG_DEBUG, "in tokenize1DArcadeParameters2, diagnostic=%s\n", *diagnostic);
	RemoveSpaces(*diagnostic);
	*object_name = strdup(strtok(NULL, delim2));
	UDA_LOG(UDA_LOG_DEBUG, "in tokenize1DArcadeParameters2, object_name=%s\n", *object_name);
	RemoveSpaces(*object_name);
	char* token = strtok(NULL, delim2);
	*extractionIndex = atoi(token);
	UDA_LOG(UDA_LOG_DEBUG, "in tokenize1DArcadeParameters2, extractionIndex1=%ld\n", *extractionIndex);
	*diagnostic2 = strdup(strtok(NULL, delim2));
	UDA_LOG(UDA_LOG_DEBUG, "in tokenize1DArcadeParameters2, diagnostic2=%s\n", *diagnostic2);
	RemoveSpaces(*diagnostic2);
	*object_name2 = strdup(strtok(NULL, delim2));
	UDA_LOG(UDA_LOG_DEBUG, "in tokenize1DArcadeParameters2, object_name2=%s\n", *object_name2);
	RemoveSpaces(*object_name2);
	token = strtok(NULL, delim2);
	*extractionIndex2 = atoi(token);
	UDA_LOG(UDA_LOG_DEBUG, "in tokenize1DArcadeParameters2, extractionIndex2=%ld\n", *extractionIndex2);
	free(s_copy);
	free(tmp);
}

void tokenizeFunParameters(const char* s, char** TOP_collections_parameters, char** attributes,
		char** normalizationAttributes)
{
	const char delim[] = ";";
	char* s_copy = strdup(s);
	char* tmp = strdup(strtok(s_copy, delim)); //function name
	*TOP_collections_parameters = strdup(strtok(NULL, delim));
	RemoveSpaces(*TOP_collections_parameters);
	*attributes = strdup(strtok(NULL, delim));
	RemoveSpaces(*attributes);
	char* token = strtok(NULL, delim);
	if (token != NULL) {
		*normalizationAttributes = strdup(token);
		RemoveSpaces(*normalizationAttributes);
	}
	free(s_copy);
	free(tmp);
}

void tokenizeFunParametersWithChannels(const char* s, char** unvalid_channels, char** TOP_collections_parameters,
		char** attributes, char** normalizationAttributes)
{
	const char delim[] = ";";
	char* s_copy = strdup(s);
	char* s1 = strdup(strtok(s_copy, delim)); //function name
	UDA_LOG(UDA_LOG_DEBUG, "fun name : %s\n", s1);
	*unvalid_channels = strdup(strtok(NULL, delim));
	UDA_LOG(UDA_LOG_DEBUG, "unvalid channels : %s\n", *unvalid_channels);
	*TOP_collections_parameters = strdup(strtok(NULL, delim));
	RemoveSpaces(*TOP_collections_parameters);
	*attributes = strdup(strtok(NULL, delim));
	RemoveSpaces(*attributes);
	char* token = strtok(NULL, delim);
	if (token != NULL) {
		*normalizationAttributes = strdup(token);
		RemoveSpaces(*normalizationAttributes);
	}
	free(s_copy);
	free(s1);
}

void tokenize_set_channels_validity(const char* s, char** unvalid_channels, char** attributes)
{
	const char delim[] = ";";
	char* s_copy = strdup(s);
	char *s1 = strdup(strtok(s_copy, delim)); //function name
	*unvalid_channels = strdup(strtok(NULL, delim)); //example: unvalid_channels:2:1,2
	*attributes = strdup(strtok(NULL, delim));
	RemoveSpaces(*attributes);
	free(s_copy);
	free(s1);
}

void getUnvalidChannelsSize(char* unvalid_channels, Longint* size)
{
	const char delim[] = ":";
	char* s_copy = strdup(unvalid_channels);
	char* token = strdup(strtok(s_copy, delim)); //should return "unvalid_channels" string
	token = strdup(strtok(NULL, delim)); //return the number of unvalid channels
	*size = atoi(token);
	free(s_copy);
	free(token);
}

void getUnvalidChannels(char* unvalid_channels, Longint* v)
{
	const char delim[] = ":";
	char* s_copy = strdup(unvalid_channels);
	char* token = strdup(strtok(s_copy, delim)); //should return "unvalid_channels" string

	token = strdup(strtok(NULL, delim)); //return the number of unvalid channels
	Longint n = atoi(token);

	UDA_LOG(UDA_LOG_DEBUG, "unvalid channels count: %ld\n", n);
	token = strdup(strtok(NULL, delim)); //return for example "1,2" if channels 1 and 2 are not valid
	UDA_LOG(UDA_LOG_DEBUG, "unvalid channels list: %s\n", token);

	const char delim2[] = ",";
	char* s_copy2 = strdup(token);

	Longint i;
	for (i = 0; i < n; i++) {
		if (i == 0) {
			v[i] = atoi(strdup(strtok(s_copy2, delim2)));
		} else {
			token = strdup(strtok(NULL, delim2));
			v[i] = atoi(token);
		}
	}
	free(s_copy);
	free(s_copy2);
	free(token);
}

Longint isChannelValid(Longint channel_number, Longint* unvalid_channels_list, Longint unvalid_channels_list_size)
{
	Longint i;
	//UDA_LOG(UDA_LOG_ERROR, "WEST:ERROR: not valid channels list size : %ld\n", unvalid_channels_list_size);
	for (i = 0; i < unvalid_channels_list_size; i++) {
		//UDA_LOG(UDA_LOG_ERROR, "WEST:ERROR: not valid channels list[i] : %ld\n", unvalid_channels_list[i]);
		if (unvalid_channels_list[i] == channel_number) {
			return 0;
		}
	}
	return 1;
}

Longint getCommand(Longint i, char** command, const char* TOP_collections_parameters)
{
	UDA_LOG(UDA_LOG_DEBUG, "In getCommand, i: %ld\n", i);
	char* s_copy = strdup(TOP_collections_parameters);
	const char delim[] = ",";
	Longint j = 0;
	char* token = strdup(strtok(s_copy, delim));
	UDA_LOG(UDA_LOG_DEBUG, "In getCommand, token: %s\n", token);
	if (token == NULL) {
		return -1;
	}
	while (token != NULL) {
		if (i == j) {
			*command = strdup(token);
			RemoveSpaces(*command);
			free(s_copy);
			return 0;
		}
		token = strtok(NULL, delim);
		j++;
	}
	free(s_copy);
	return -1;
}

void getTopCollectionsCount(const char* TOP_collections_parameters, Longint* collectionsCount)
{
	*collectionsCount = 0;
	char* s_copy = strdup(TOP_collections_parameters);
	const char delim[] = ",";
	char* token = strtok(s_copy, delim);
	while (token != NULL) {
		(*collectionsCount)++;
		token = strtok(NULL, delim);
	}
	free(s_copy);
	free(token);
}

Longint getNormalizationFactor(Double* normalizationFactor, char* normalizationAttributes)
{
	char* s_copy = NULL;
	char* operation = NULL;
	char* funname = NULL;
	char* csteStr = NULL;

	if (normalizationAttributes != NULL) {
		UDA_LOG(UDA_LOG_DEBUG, "normalization attributes found\n");
		const char delim[] = ":";
		s_copy = strdup(normalizationAttributes);
		operation = strdup(strtok(s_copy, delim));
		if (strcmp("multiply", operation) == 0) {
			//UDA_LOG(UDA_LOG_DEBUG, "Multiply operation\n");
			funname = strdup(strtok(NULL, delim));
			if (strcmp("cste", funname) == 0) {
				//UDA_LOG(UDA_LOG_DEBUG, "multiply data by constant value\n");
				csteStr = strdup(strtok(NULL, delim));
				//UDA_LOG(UDA_LOG_DEBUG, "%s\n", csteStr);
				*normalizationFactor = atof(csteStr);
			} else {
				int err = 901;
				//UDA_LOG(UDA_LOG_ERROR, "Unsupported operand for 'multiply' operation\n");
				addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: unsupported operand for 'multiply' operation", err,
						"");
				return -1;
			}

		} else {
			int err = 901;
			//UDA_LOG(UDA_LOG_ERROR, "Unsupported operation to apply\n");
			addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: unsupported operation to apply", err, "");
			return -1;
		}
	} else {
		UDA_LOG(UDA_LOG_DEBUG, "no normalization attributes found\n");
	}
	free(s_copy);
	free(operation);
	free(funname);
	free(csteStr);
	return 0;
}

void multiplyDouble(Double* p, Double factor, Longint val_nb)
{
	//UDA_LOG(UDA_LOG_DEBUG, "Entering multiplyDouble...\n");
	//DAM_LOGF(UDA_LOG_DEBUG, "val_nb : %ld\n", val_nb);
	//UDA_LOG(UDA_LOG_DEBUG, "factor : %f\n", factor);
	if (factor != 1) {
		Longint i;
		for (i = 0; i < val_nb; i++) {
			p[i] *= factor;
		}
	}
}

void multiplyInt(Longint* p, Double factor, Longint val_nb)
{
	if (factor != 1) {
		Longint i;
		for (i = 0; i < val_nb; i++)
			p[i] *= (Longint)factor;
	}
}

void maxValueOfAbs(Double* v, Longint val_nb, Double mincst, Double relative_error) {
	Longint i;
	for (i = 0; i < val_nb; i++)
		 v[i] = fmaxf(relative_error*fabs(v[i]), mincst);
}

Longint getNumIDAMIndex(char* attributes, Longint* nodeIndices)
{

	char* s_copy = strdup(attributes);
	const char delim[] = ":";
	char* charIDAMIndex = NULL;
	strtok(s_copy, delim); //rank
	strtok(NULL, delim); //type
	charIDAMIndex = strdup(strtok(NULL, delim)); //#0
	char firstChar;
	firstChar = charIDAMIndex[0];

	if (firstChar == '#') {
		UDA_LOG(UDA_LOG_DEBUG, "index specified in IDAM request\n");
		return nodeIndices[atoi(&charIDAMIndex[1])] - 1;
	} else {
		UDA_LOG(UDA_LOG_DEBUG, "idam index hard coded in mapping file\n");
		return atoi(&firstChar) - 1;
	}
	free(s_copy);
	free(charIDAMIndex);
}

Longint getNumIDAMIndex2(char* s, Longint* nodeIndices)
{

	char firstChar;
	firstChar = s[0];

	if (firstChar == '#') {
		UDA_LOG(UDA_LOG_DEBUG, "index specified in IDAM request\n");
		return nodeIndices[atoi(&s[1])] - 1;
	} else {
		UDA_LOG(UDA_LOG_DEBUG, "no index specified\n");
		return -1;
	}
}

Longint getReturnType(char* attributes, Longint* dataType)
{
	//UDA_LOG(UDA_LOG_DEBUG, "attributes3: %s\n", attributes);
	char* s_copy = strdup(attributes);
	const char delim[] = ":";
	strtok(s_copy, delim); //the rank
	char* token = strtok(NULL, delim);
	//UDA_LOG(UDA_LOG_DEBUG, " token: %s\n", token);

	Longint i = UDA_TYPE_UNKNOWN;

	int err = 0;

	if (strcmp(token, "vecstring_type") == 0 || strcmp(token, "string") == 0 || strcmp(token, "STR_0D") == 0) {
		i = UDA_TYPE_STRING;
	} else if (strcmp(token, "vecflt_type") == 0 || strcmp(token, "Double") == 0 || strcmp(token, "FLT_0D") == 0) {
		i = UDA_TYPE_DOUBLE;
	} else if (strcmp(token, "float") == 0) {
		i = UDA_TYPE_FLOAT;
	} else if (strcmp(token, "vecint_type") == 0 || strcmp(token, "integer") == 0 || strcmp(token, "int") == 0 ||
			strcmp(token, "INT_0D") == 0) {
		i = UDA_TYPE_INT;
	} else {
		err = 901;
		//UDA_LOG(UDA_LOG_ERROR, "%s", "WEST:ERROR: convertToInt(): Unsupported data type");
		addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: convertToInt(): Unsupported data type: %s", err, token);
		return -1;
	}
	*dataType = i;
	free(s_copy);
	return 0;
}

void getRank(char* attributes, Longint* rank)
{
	char* s_copy = strdup(attributes);
	const char delim[] = ":";
	char* rankStr = strdup(strtok(s_copy, delim));
	*rank = atoi(&rankStr[0]);
	free(s_copy);
	free(rankStr);
}

void getValueCollect(char* command, char** value, Longint* nodeIndices)
{
	char* s_copy = strdup(command);
	const char delim[] = ":";
	strtok(s_copy, delim); //prod_name
	strtok(NULL, delim); //object name
	strtok(NULL, delim); //param name
	*value = strdup(strtok(NULL, delim)); //value for the setvalue_collect function
	char* token = strtok(NULL, delim);
	if (token != NULL) {
		Longint UDAIndex = getNumIDAMIndex2(token, nodeIndices);
		char str[2];
		sprintf(str, "%s", "_");
		sprintf(str, "%ld", UDAIndex);
		*value = strcat(*value, str);
	}
	free(s_copy);
}

void tokenizeCommand(const char* s, char** prod_name, char** obj_name, char** param_name, char** flag)
{
	char* s_copy = strdup(s);
	const char delim[] = ":";
	//UDA_LOG(UDA_LOG_DEBUG, "Tokenizing: %s\n", s);
	*prod_name = strdup(strtok(s_copy, delim));
	RemoveSpaces(*prod_name);
	//UDA_LOG(UDA_LOG_DEBUG, "%s\n", *prod_name);
	*obj_name = strdup(strtok(NULL, delim));
	RemoveSpaces(*obj_name);
	//UDA_LOG(UDA_LOG_DEBUG, "%s\n", *obj_name);
	*param_name = strdup(strtok(NULL, delim));
	RemoveSpaces(*param_name);
	char* token = strtok(NULL, delim);
	if (token != NULL) {
		*flag = strdup(token);
		RemoveSpaces(*flag);
	}
	free(s_copy);
}

void getObjectName(char** obj_name, char* command)
{
	char* s_copy = strdup(command);
	const char delim[] = ":";
	char* s = strdup(strtok(s_copy, delim));
	*obj_name = strdup(strtok(NULL, delim));
	RemoveSpaces(*obj_name);
	free(s_copy);
	free(s);
}

void searchIndices(Longint requestedIndex, Longint* l, Longint* searchedArray, Longint* searchedArrayIndex)
{
	*searchedArray = 0;
	*searchedArrayIndex = 0;

	if (requestedIndex < l[0]) {

		*searchedArrayIndex = requestedIndex; //we take the (requestedIndex) signal in the signals group
		*searchedArray = 0; //we take the first group of signals which appears in the tsmat_collect string

	} else if (requestedIndex == l[0]) {

		*searchedArrayIndex = 0;
		*searchedArray = 1;

	} else if (requestedIndex > l[0]) {

		Longint i = 0;

		Longint d = requestedIndex - l[0];

		while (d >= 0) {
			i++;
			d = d - l[i];
		}

		Longint k = i - 1;
		Longint j;
		Longint s = 0;
		for (j = 0; j <= k; j++) {
			s += l[j];
		}
		*searchedArrayIndex = requestedIndex - s;
		*searchedArray = k + 1;
	}
}


void addExtractionChars(char* result, const char* signalName, Longint extractionIndex)
{
	strcpy(result, signalName);
	strcat(result, "!");
	char s[5];
	sprintf(s, "%ld", extractionIndex);
	strcat(result, s);
}

void RemoveSpaces(char* source)
{
	char* i = source;
	char* j = source;
	while (*j != 0) {
		*i = *j++;
		if (*i != ' ') {
			i++;
		}
	}
	*i = 0;
}

void printDataBlockPreview(DATA_BLOCK* db, const char* signal_name)
{
    if (!db || !db->data || db->data_n <= 0) {
        printf("[printDataBlockPreview] %s : vide ou non initialisé\n", signal_name);
        return;
    }

    printf("[printDataBlockPreview] %s → %d points", signal_name, (int)db->data_n);

    // Affichage du type pour info
    if (db->data_type == UDA_TYPE_FLOAT)  printf(" (float)\n");
    else if (db->data_type == UDA_TYPE_DOUBLE) printf(" (double)\n");
    else if (db->data_type == UDA_TYPE_INT)    printf(" (int)\n");
    else printf(" (type=%d)\n", db->data_type);

    int n = (db->data_n < 10) ? db->data_n : 10;

    printf("    Premières valeurs : ");
    for (int i = 0; i < n; i++) {
        if (db->data_type == UDA_TYPE_DOUBLE) {
            double* d = (double*)db->data;
            printf("%.6g ", d[i]);
        }
        else if (db->data_type == UDA_TYPE_FLOAT) {
            float* f = (float*)db->data;
            printf("%.6g ", (double)f[i]);
        }
        else if (db->data_type == UDA_TYPE_INT) {
            int* vi = (int*)db->data;
            printf("%d ", vi[i]);
        }
        else {
            printf("??  ");
			//char* s = NULL;
			/*xmlChar* xPath;
			//setReturnDataString(db, (char*)xPath, nullptr);
			print("%s ", (char*)xPath);*/
        }
    }
    if (db->data_n > 10) printf("... (%d valeurs de plus)", (int)db->data_n - 10);
    printf("\n");
	
}

Longint execute_setvalue_collect(const char* TOP_collections_parameters, char* attributes,
		Longint shotNumber, Longint* nodeIndices, char* normalizationAttributes)
{

	Longint collectionsCount;
	getTopCollectionsCount(TOP_collections_parameters, &collectionsCount);

	Longint* l;
	l = (Longint*)calloc(collectionsCount, sizeof(Longint));

	Longint i;
	Longint status = -1;
	for (i = 0; i < collectionsCount; i++) {
		char* command = NULL;
		status = getCommand(i, &command, TOP_collections_parameters);
		if (status == -1) {
			int err = 901;
			//UDA_LOG(UDA_LOG_ERROR, "%s", "WEST:ERROR: unable to get the shapeof command");
			free(command);
			free(l);
			addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: unable to get the shapeof command", err, "");
			
			return status;
		}

		Longint nb_val = 0;
		status = getShapeOf(command, shotNumber, &nb_val, 0);
		if (status != 0){  
			free(command);
			return status;
		}	
		l[i] = nb_val;
	}

	Longint requestedIndex = getNumIDAMIndex(attributes, nodeIndices);

	Longint searchedArray;
	Longint searchedArrayIndex;

	searchIndices(requestedIndex, l, &searchedArray, &searchedArrayIndex);
	UDA_LOG(UDA_LOG_DEBUG, "searchedArray : %ld\n", searchedArray);
	UDA_LOG(UDA_LOG_DEBUG, "searchedArrayIndex : %ld\n", searchedArrayIndex);

	char* command = NULL;
	status = getCommand(searchedArray, &command, TOP_collections_parameters);
	if (status != 0){  
		free(command);
		return status;
	}	

	char* value;
	getValueCollect(command, &value, nodeIndices);
	UDA_LOG(UDA_LOG_DEBUG, "Command : %s\n", command);

	Longint data_type;
	status = getReturnType(attributes, &data_type);
	if (status != 0){  
		free(value);
		free(command);
		return status;
	}	

	char* buffer = setBuffer(data_type, value);

	UDA_LOG(UDA_LOG_DEBUG, "Found value: %s\n", value);

	Double normalizationFactor = 1;
	status = getNormalizationFactor(&normalizationFactor, normalizationAttributes);
	if (status != 0){  
		free(value);
		free(command);
		free(buffer);
		return status;
	}	

	//setStaticValue(data_type, data_block, buffer, 0, normalizationFactor);

	free(value);
	free(command);
	free(buffer);
	return 0;
}

Longint getShapeOf(const char* command, Longint shotNumber, Longint* nb_val, Longint option)
{

	char* prod_name = NULL; //DMAG, ...
	char* object_name = NULL;
	char* param_name = NULL;
	char* flag = NULL;

	UDA_LOG(UDA_LOG_DEBUG, "TEST:: In getShapeOf, calling tokenizeCommand with command: %s\n", command);

	//Tokenize mapfun string to get function parameters, return type and arguments (#1, #2,...) to use
	tokenizeCommand(command, &prod_name, &object_name, &param_name, &flag);
	char *ptr = NULL;
	//get the size of available data
	UDA_LOG(UDA_LOG_DEBUG, "TEST:: DEBUG : prod_name: %s\n", prod_name);
	UDA_LOG(UDA_LOG_DEBUG, "TEST:: DEBUG : object: %s\n", object_name);
	UDA_LOG(UDA_LOG_DEBUG, "TEST:: DEBUG : param: %s\n", param_name);
	int val_nb = 1;
    int format;
	Longint status = tsrqparm((char**) &ptr, nb_val, shotNumber, prod_name, object_name, param_name, val_nb, &format);
	UDA_LOG(UDA_LOG_DEBUG, "TEST:: tsrqparm status: %ld\n", status);
	UDA_LOG(UDA_LOG_DEBUG, "TEST:: tsrqparm nb_val: %ld\n", *nb_val);
	
	if (status != 0) {
		UDA_LOG(UDA_LOG_DEBUG, "TEST:: Error calling tsrqparm\n");
		int err = 901;
		UDA_LOG(UDA_LOG_ERROR, "%s: %s: %s: %s, shot:%ld\n", "WEST:ERROR: unable to get shape of static data", prod_name, object_name, param_name, shotNumber);
		free(prod_name);
		free(object_name);
		free(param_name);
		free(flag);
		free(ptr);
		//addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: unable to get shape of static data", err, "");
		return status;
	}

	/*UDA_LOG(UDA_LOG_DEBUG,"TEST:: INT16=%d\n", INT16);
        UDA_LOG(UDA_LOG_DEBUG,"TEST:: OCTET=%d\n", OCTET);
        UDA_LOG(UDA_LOG_DEBUG,"TEST:: INT32=%d\n", INT32);

        UDA_LOG(UDA_LOG_DEBUG,"TEST:: format=%d\n", format);*/

	if (option == 2 && (format==INT16 || format==OCTET)) {
	  short *v = (short *) ptr; 
	  *nb_val = (int) *v;
	  UDA_LOG(UDA_LOG_DEBUG, "TEST:: short from getShapeOf, nb_val=%d\n", *nb_val);
	}
        else if (option == 2 && format==INT32) {
           int *v = (int *) ptr;
           *nb_val = *v;    
           UDA_LOG(UDA_LOG_DEBUG, "TEST::int from getShapeOf, nb_val=%d\n", *nb_val);     
        }
        else if (option==2) { 
           int err = 901;
           UDA_LOG(UDA_LOG_ERROR, "WEST:ERROR: getShapeOf: Unexpected datatype returned by tsrqparm!");
		   free(prod_name);
		   free(object_name);
		   free(param_name);
		   free(flag);
		   free(ptr);
           //addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: getShapeOf: Unexpected datatype returned by tsrqparm!", err, "");
        }

	free(prod_name);
	free(object_name);
	free(param_name);
	free(flag);
	free(ptr);
	return 0;
}


char* setBuffer(Longint data_type, const char* value)
{
	char* buffer = NULL;

	if (data_type == UDA_TYPE_FLOAT) {
		UDA_LOG(UDA_LOG_DEBUG, "UDA_TYPE_FLOAT requested from WEST plugin\n");
		buffer = (char*) malloc(sizeof(float));
		float* f_buf = (float*)buffer;
		*f_buf = atof(value);
		UDA_LOG(UDA_LOG_DEBUG, "Testing float value : %f\n", *f_buf);
	} else if (data_type == UDA_TYPE_DOUBLE) {
		UDA_LOG(UDA_LOG_DEBUG, "UDA_TYPE_DOUBLE requested from WEST plugin\n");
		buffer = (char*) malloc(sizeof(double));
		double* f_buf = (double*)buffer;
		*f_buf = atof(value);
	} else if (data_type == UDA_TYPE_INT) {
		UDA_LOG(UDA_LOG_DEBUG, "UDA_TYPE_INT requested from WEST plugin\n");
		buffer = (char*) malloc(sizeof(Longint));
		Longint* i_buf = (Longint*)buffer;
		*i_buf = atoi(value);
	} else if (data_type == UDA_TYPE_STRING) {
		UDA_LOG(UDA_LOG_DEBUG, "UDA_TYPE_STRING requested from WEST plugin\n");
		buffer = strdup(value);
	} else {
		int err = 901;
		UDA_LOG(UDA_LOG_DEBUG, "Unsupported data type in setBuffer(): %ld\n", data_type);
		//UDA_LOG(UDA_LOG_ERROR, "%s", "WEST:ERROR: unsupported data type");
		addIdamError(UDA_CODE_ERROR_TYPE, "WEST:ERROR: unsupported data type", err, "");
	}

	return buffer;
}
