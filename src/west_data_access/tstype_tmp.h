#ifndef TSTYPE_H
#define TSTYPE_H

// Types de base pour le code legacy WEST
typedef int Longint;
typedef double Double;

// Codes de format TSLib (utilisés dans ts_rqparm.cpp)
#define OCTET 1
#define STRING12 2
#define INT16 3
#define INT32 4
#define REEL16 5
#define REEL32 6
#define TWIN_INT16 7
#define TWIN_REEL32 8
#define INT_REEL32 9
#define VOIE 10
#define FONCTION 11
#define VOIE_GAIN 12
#define REGISTRE 13
#define F_STRAT_DIAG 14
#define STRAT_PILOTE 15
#define DECL_COND 16
#define EVT_EXTERNE 17
#define SERNAM 18
#define CADRAN 19
#define LIEN 20
#define DECL_SEQ 21
#define VOIE_SEQ 22
#define TAB_SEQ 23
#define T_DECODE 24
#define T_IT 25
#define T_ENCODE 26
#define F_COMMON 27
#define F_CHRONO 28
#define T_DECLENC 29
#define L_DIAG 30
#define T_DECLENCHE 31
#define TEXTE 32
#define F_TOPMSDIV 33
#define GRAPHE 34
#define SIGNAL 35
#define INT2_CHAR64 36
#define FLOAT_CHAR64 37
#define F_ACHRONO 38
#define F_DESCRIPTEUR 39

// Constantes de types UDA (pour remplacer udaTypes.h)
#define UDA_TYPE_UNKNOWN 0
#define UDA_TYPE_CHAR    1
#define UDA_TYPE_SHORT   2
#define UDA_TYPE_INT     3
#define UDA_TYPE_UNSIGNED_INT 4
#define UDA_TYPE_LONG    5
#define UDA_TYPE_FLOAT   6
#define UDA_TYPE_DOUBLE  7
#define UDA_TYPE_STRING  8

// Structure DATA_BLOCK pour remplacer celle d'UDA
typedef struct DATA_BLOCK {
    int data_type;          // Type de données (UDA_TYPE_...)
    int rank;               // Rang (0 pour scalaire, 1 pour vecteur, etc.)
    unsigned int dims[64];  // Dimensions
    char* data;             // Pointeur vers les données brutes (alloué via malloc)
    int data_n;             // Nombre total d'éléments
    
    int errcode;            // Code d'erreur
    char error_msg[1024];   // Message d'erreur
    
    int order;              // Champ legacy
} DATA_BLOCK;

#endif // TSTYPE_H