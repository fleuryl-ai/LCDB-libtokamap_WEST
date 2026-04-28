#ifndef WEST_LOGGING_H
#define WEST_LOGGING_H

#include <stdio.h>

// Définition des niveaux de log (compatibilité UDA)
#define UDA_LOG_DEBUG 1
#define UDA_LOG_INFO  2
#define UDA_LOG_WARN  3
#define UDA_LOG_ERROR 4
#define UDA_LOG_NONE  5

// Niveau de log actuel (modifier cette valeur pour filtrer, ex: UDA_LOG_INFO)
#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL UDA_LOG_DEBUG
#endif

// Macro de remplacement pour UDA_LOG
// Utilise fprintf(stderr, ...) pour afficher les logs simplement
#define UDA_LOG(level, fmt, ...) \
    do { \
        if (level >= CURRENT_LOG_LEVEL) { \
            fprintf(stderr, "[WEST] "); \
            fprintf(stderr, fmt, ##__VA_ARGS__); \
        } \
    } while(0)

// Définition pour la gestion d'erreur (implémentation vide)
#define UDA_CODE_ERROR_TYPE 1

inline void addIdamError(int type, const char* msg, int code, const char* loc) {
    (void)type; (void)msg; (void)code; (void)loc;
}

#endif // WEST_LOGGING_H