#ifndef TSTYPE_H
#define TSTYPE_H

// Types de base pour le code legacy WEST
typedef int Longint;
typedef double Double;



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