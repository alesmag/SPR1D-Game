#include "../../Utils/Utils.h"
#ifndef PROGETTOFINALE_IMPICCATO_H
#define PROGETTOFINALE_IMPICCATO_H

#define DEFAULT_DICTIONARY "default.txt"
#define NUM_TENTATIVI 4
#define MAX_LEN_RIGA 119
#define MAX_RIGHE 50
#define LETTERA_A_MIN 'a'
#define LETTERA_Z_MIN 'z'
#define LETTERA_A_MAIUSC 'A'
#define LETTERA_Z_MAIUSC 'Z'

#endif //PROGETTOFINALE_IMPICCATO_H

// permette di selezionare una riga dal file
char *selectRigaFile(int r, char *nome_file);

// conta il numero delle righe nel file e ne restituisce il numero
int numRigheFile(char *nome_file);

// inizializza la frase da indovinare
void initSegreta(char * str, char *segreta);

// controlla se la lettera è corretta all'interno della frase segreta
bool isLetteraCorretta(char *str, char l);

// sostituisce lo spazio della frase segreta con una letytera corretta
void sostituisciLettera(char *segreta, char *str, char l);

// controlla se la frase è una frase segreta
bool isFrase(char *str, char *segreta);

// inizializza i tentativi per ogni giocatore
void initTentativi(int tentativi[QUATTRO_PLAYER]);

// controlla se un giocatore ha terminato i propri tentativi
bool isTentativiFiniti(int tentativi[QUATTRO_PLAYER]);

// gioco dell'impiccato
int impiccato(GameFile *file, Gruppo gruppo);