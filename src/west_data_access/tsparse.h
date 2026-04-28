#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#include "tstype.h"

#define SEP1		'!'	/* separateur indice 1	   */
#define SEP2		'.'	/* separateur indice 2	   */
#define SEP3		'#'	/* separateur occurrence   */

Longint tsparse(char* string, char* nomsig, Longint indices[], Longint* extr, Longint* occur);
