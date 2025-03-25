#include "../../Utils/Utils.h"

#ifndef PROGETTOFINALE_TRIS_H
#define PROGETTOFINALE_TRIS_H

#define PLAYER_X -2
#define PLAYER_O -3

#endif //PROGETTOFINALE_TRIS_H

// carica la matrice del tris con valori numerici utili per selezionare una cella
void loadMatrix(int tris[TRE][TRE]);

// stampa a video la matrice del tris
void showMatrix(int tris[TRE][TRE]);

// trova la posizione di una cella
int findPos(int tris[TRE][TRE], int cell[DUE], int pos);

// controlla se la partita è stata vinta e ne restituisce il vincitore
int isVintaTris(Gruppo gruppo, int tris[TRE][TRE], int symbol);

// imposta un simbolo nella cella selezionata
int setMatrix(int tris[TRE][TRE], int cell[DUE], int pos, int symbol);

// controlla se la matrice del tris è piena, restituisce true se lo è altrimenti false
bool isTrisPieno(int tris[TRE][TRE]);

// gioco del tris
int tris(GameFile *file, Gruppo gruppo);