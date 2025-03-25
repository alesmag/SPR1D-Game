#include "../../Utils/Utils.h"

#ifndef PROGETTOFINALE_SCREMATURA_H
#define PROGETTOFINALE_SCREMATURA_H

#define MAX_NUM 999

#endif //PROGETTOFINALE_SCREMATURA_H

// permette alla cpu di fare le proprie scelte su criteri randomici
int sceltaCpu(int numMin, int numMag);

// permette al giocatore di fare le proprie scelte tramite valori presi in input
int sceltaGiocatore(int numMin, int numMag);

// inizializza i vettori numMin e numMag
void initVett(Gruppo gruppo, int *numMin, int *numMag);

// controlla se la partita è stata vinta e ne restituisce il vincitore
int isVinta(Gruppo gruppo, int scelta, int num, int *numMin, int *numMag, int i, bool cond);

// gioco dell'indovina il numero
int scrematura(GameFile *file, Gruppo gruppo);