#include "../../Utils/Utils.h"

#ifndef PROGETTOFINALE_BIGLIE_H
#define PROGETTOFINALE_BIGLIE_H

#define START_NUM_BIGLIE 10

#endif //PROGETTOFINALE_BIGLIE_H

// permette al giocatore di scommettere un determinato numero di biglie
void scommessaGiocatore(int *numBiglie, int *biglieScomm, int j);

// permette alla cpu di scommettere un determinato numero di biglie in modo casuale
void scommessaCpu(int *numBiglie, int *biglieScomm, int j);

// permette al giocatore di scegliere se l'altro giocatore ha scelto un numero pari o dispari di biglie
void pdGiocatore(int *pd, int i);

// permette alla cpu di scegliere se l'altro giocatore ha scelto un numero pari o dispari di biglie, in modo casuale
void pdCpu(int *pd, int i);

// distribuisce il numero di biglie tra i giocatori
void distribuzioneBiglie(int *biglieScomm, int *numBiglie, int *pd, int i);

// controlla se la partita è stata vinta e ne restituisce il vincitore
int isVintaBiglie(int *numBiglie, Gruppo gruppo, int i);

// gioco delle biglie
int biglie(GameFile *file, Gruppo gruppo);
