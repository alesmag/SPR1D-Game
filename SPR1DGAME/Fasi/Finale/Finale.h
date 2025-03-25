#include "../../Utils/Utils.h"
#include "../../Giochi/Giochi.h"
#include "../Svolgimento/Svolgimento.h"

#ifndef PROGETTOFINALE_FINALE_H
#define PROGETTOFINALE_FINALE_H

#endif //PROGETTOFINALE_FINALE_H

#define CARTE 52
#define FACCE 13
#define BLACKJACK 21
#define VALORE_TOTALE_ASSO_MAX 10
#define VALORE_ASSO_MIN 1
#define VALORE_ASSO_MAX 11
#define VALORE_MAX_RISCHIO 19
#define VAL_FIGURE 10
#define PARITA -2

typedef enum {Asso, Due, Tre, Quattro, Cinque, Sei, Sette, Otto, Nove, Dieci, Fante, Regina, Re} Faccia;
typedef enum {Cuori, Quadri, Fiori, Picche} Seme;

// struttura per rappresentare una singola carta
typedef struct
{
  Faccia faccia;
  Seme seme;
} Carta;

// struttura per rappresentare la mano di gioco di un giocatore
typedef struct
{
  int valTot;
  bool isBot;
} ManoGiocatore;

// crea il gruppo finale composto da due giocatori
Gruppo* creaGruppoFinale(GameFile *file, int numGruppi);

// stampa a video il gruppo finale
void printGruppoFinale(Gruppo gruppo);

// riempie il mazzo di carte
void riempiMazzo(Carta *mazzo);

// mischia il mazzo di carte
void mischia(Carta *mazzo);

// restituisce il valore di una carta
int valCarta(Faccia faccia);

// stampa a video la faccia di una carta
char *stampaFaccia(Faccia facciaCarta);

// stampa a video il seme di una carta
char *stampaSeme(Seme seme);

// prende una carta dal mazzo
void getCarta(ManoGiocatore *mazzoGiocatore, Carta *mazzo, int *cartaAtt);

// inizializza il mazzo del giocatore
void initMazzoGiocatore(ManoGiocatore *mazzoGiocatore, GameFile file, int id);

// controlla se è stato fatto un blackjack (21) col valore totale delle carte di un giocatore
bool isBlackjack(int totale);

// controlla se il totale delle carte di un giocatore è andato oltre alla soglia di blackjack (21)
bool hasSbancato(int totale);

// controlla se la partita è stata vinta, e ne restituisce il vincitore
int isWin(ManoGiocatore *mazzoGiocatore, Gruppo gruppo, bool fine);

// distribuisce le prime due carte iniziali al giocatore
void start(GameFile file, ManoGiocatore *mazzoGiocatore, Carta *mazzo, int *cartaAtt, Gruppo gruppi);

// gioco del blackjack
int blackjack(GameFile *file, Gruppo gruppo);

// permette di giocare il gioco del blackjack
void finale(GameFile *file);