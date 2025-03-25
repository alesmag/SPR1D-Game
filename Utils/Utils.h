#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>

#ifndef PROGETTOFINALE_UTILS_H
#define PROGETTOFINALE_UTILS_H

#define NEG_VAL -1
#define DEFAULTSAVE "DefaultSave.bin"
#define MAX_LEN_NOME 64
#define DUE_PLAYER 2
#define QUATTRO_PLAYER 4
#define START_ESPONENTE 0
#define OFFSET_ESPONENTE 2
#define BASE 2
#define MIN_GIOCATORI 16
#define DEAD 0
#define ALIVE 1
#define NAME_IMMORTAL_PLAYER "Riccardo Scateni"

typedef enum {PLAYERUNO, PLAYERDUE, PLAYERTRE, PLAYERQUATTRO} players;
typedef enum {ZERO, UNO, DUE, TRE, QUATTRO, CINQUE, SEI, SETTE, OTTO, NOVE, DIECI} numeri;

// struttura per i giocatori
typedef struct
{
  int idGiocatore;
  char nome[MAX_LEN_NOME];
  int numSPR1DGiocati;
  int numFinaliGiocate;
  int numSPR1DVinti;
  int totaleGiochiGiocati;
  int totaleGiochiVinti;
} Giocatore;

// struttura per i gruppi giocatore
typedef struct
{
  int numGiocatori;
  int *giocatori;
} Gruppo;

// struttura per il file di gioco
typedef struct
{
  int numRealGiocatoriTotali;
  Giocatore *giocatori;
  bool isInCorso;
  int numGiocatoriTotali;
  int numRealGiocatoriAttuali;
  int* indexGiocatori;
  int* inGioco;
} GameFile;

#endif //PROGETTOFINALE_UTILS_H

// utilizzato per prendere in input "y" o "n" come si o no per una scelta da parte dell'utente
bool yesOrNo();

// utilizzato per premere invio e permettere al programma di continuare normalmente
void enter();

// inizializza un giocatore con tutte le sue informazioni (id, nome, etc)
Giocatore initGiocatore(int id, char *nome);

// stampa le informazioni di un giocatore a video
void stampaGiocatore(Giocatore giocatori);

// stampa le informazioni di più giocatori a video
void stampaGiocatori(Giocatore *giocatori, int size);

// controlla se in un gruppo vi sono soltanto giocatori controllati dal computer (restituisce true se vero, false se almeno un giocatore non è una cpu)
bool cpuOnlyGruppo(GameFile file, Gruppo gruppo);

// controlla se un giocatore è una cpu (restituisce true se lo è, altrimenti restituisce false)
bool isCpu(GameFile file, int giocatoreGruppo);

// salva le informazioni contenute nella struttura GameFile in un file .bin, salvando effettivamente i dati della partita in corso
void salvaFile(GameFile file, char* filename);

// carica un file .bin dal computer, aggiornando le informazioni nella struttura GameFile
GameFile caricaFile(char* filename);

// calcola il numero di gruppi giocatore restituendo l'esponente della potenza
int numGruppiPlayers(int size);

// elimina i giocatori (sia cpu che non) che hanno perso una partita
void uccidiPlayer(GameFile *file, Gruppo gruppo, int winner);

// inizializza il vettore inGioco della struttura GameFile, al valore "ALIVE"
void initInGioco(GameFile *file);

// conta il numero dei giocatori ancora in gioco (ALIVE) e ne restituisce il numero
int countNumAlive(GameFile file);

// inizializza il vettore inGioco della struttura GameFile, al valore "ALIVE"
void alivePlayers(GameFile file, int *idNumAlive);

// stampa i gruppi con gli id dei giocatori che ci sono all'interno di ogni gruppo
void printGruppi(Gruppo *gruppi, int numGruppi);

// permette di selezionare giocatori inseriti, se selezionati permette di scegliere l'id da assegnare al giocatore
void assegnaGiocatori(GameFile *file);

// crea i gruppi giocatori per la parte della scrematura. Vi sarà al massimo una differenza di un giocatore per i gruppi
Gruppo* creaGruppiIniziali(GameFile *file, int numGruppi);

// permette di far scegliere all'utente se salvare o no la partita, in caso venga salvata verrà richiesto il nome del file da salvare
void sceltaSalvataggio(GameFile file);

// permette di inserire il nome del file da caricare nella partita
char *sceltaCaricamento();

// permette di inserire il numero di giocatori prima di iniziare la partita
int numGiocatori();

// inizializza il vettore inGioco della struttura GameFile, al valore "ALIVE"
void abilitaGiocatori(GameFile *file);

// trova la posizione di un giocatore nel vettore
int findPosGiocatore(GameFile file, int giocatore);

// aggiorna le statistiche dei giocatori nel file
void aggiornaStats(GameFile *file, Gruppo gruppo, int winner, bool isFinale);

// esegue una ricerca per nome del giocatore
int searchName(char *name,Giocatore *giocatori,int dim);

// controlla se un determinato id giocatore si trova nel gruppo
int isPlayerInGroup(int id, int *array_id, int dim);

// permette di resettare il file di gioco, così da poter utilizzare gli stessi giocatori per una seguente nuova partita
void resetGamefile(GameFile *file);