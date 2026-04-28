#include "tstype.h"

#define sigType 	1
#define homoType 	2
#define extgType 	3

#define CTPS	(double) 1e6	/* pour avoir des secondes */
#define MAX_COORD	4	/* Nbre max de coordonnees d'un groupe */
#define MAX_SIG  	128	/* Nbre max de signaux d'un groupe     */
#define TAILLE_MISC	256	/* Taille des certifs,date,heure ..    */
#define NONFATAL	0	/* erreur non fatale	*/
#define FATAL		1	/* erreur fatale	*/
#define S_SIMPLE	2	/* signal simple	*/

#define D_BRUTE		0	/* donnee brute			*/
#define D_TRAITEE	1	/* donnee traitee		*/
#define S_SIMPLE	2	/* signal simple		*/
#define D_AGHHETERO	3	/* donnee d'un groupe hetero	*/
#define D_GHOMO		4	/* groupe homogene		*/
#define D_GHETERO	5	/* groupe heterogene		*/
#define SG_FTMPS	6	/* signal fonction du temps	*/
#define D_REDUITE	7	/* donnee reduite		*/
#define D_PRETRAITE	8	/* donnee pretraitee		*/
#define D_CALCULEE	9	/* donnee calculee		*/
#define D_RTEMPO	10	/* donnee reduite temporelle	*/

#define LONG_UNITE	8

Longint tsrqparm(char** pt_char_address, Longint* nb_val, Longint num_choc, const char* nom_prod, const char* nom_objet, const char* nom_param, Longint val_nb, int *format);
Longint readSignal(char *nomsigp, Longint numchoc, Longint occ, Longint *rang, Double **X, Double **Y, Longint* len);
void getSignalType(char* nomsig, Longint numchoc, Longint *signalType);
void getExtractionsCount(char* nomsigp, Longint numchoc, Longint occ, Longint* extractionCount);



