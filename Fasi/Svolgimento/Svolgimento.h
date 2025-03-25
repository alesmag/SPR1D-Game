#include "../../Utils/Utils.h"
#include "../../Giochi/Giochi.h"

#ifndef PROGETTOFINALE_SVOLGIMENTO_H
#define PROGETTOFINALE_SVOLGIMENTO_H

typedef enum {PARIDISPARI, DADI, MORRACINESE, MURRA, TRIS, BIGLIE, IMPICCATO} giochi;

#endif //PROGETTOFINALE_SVOLGIMENTO_H

// stampa il nome del gioco scelto
void printGioco(giochi gioco);

// crea i gruppi giocatori per lo svolgimento, questi gruppi saranno composti ciascuni da 2 o da 4 giocatori
Gruppo* creaGruppiSvolgimento(GameFile *file, int numGruppi);

// nella fase di svolgimento vengono scelti dei giochi casualmente
void svolgimento(GameFile *file);