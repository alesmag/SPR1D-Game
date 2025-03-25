#include "../Utils/Utils.h"
#include "Scrematura/Scrematura.h"


Giocatore initGiocatore(int id,char *nome)
{
  Giocatore giocatore;

  giocatore.idGiocatore = id;
  strcpy(giocatore.nome, nome);
  giocatore.numSPR1DGiocati = ZERO;
  giocatore.numFinaliGiocate = ZERO;
  giocatore.numSPR1DVinti = ZERO;
  giocatore.totaleGiochiGiocati = ZERO;
  giocatore.totaleGiochiVinti = ZERO;

  return giocatore;
}

void initInGioco(GameFile *file)
{
  int i;

  file->inGioco = malloc(sizeof(int) * file->numGiocatoriTotali);

  for(i = ZERO; i < file->numGiocatoriTotali; i++)
    file->inGioco[i] = ALIVE;
}

void creaGiocatori(GameFile *file, int num)
{
  int i;
  char *nome;

  file->giocatori = malloc(sizeof (Giocatore)*num);
  file->numRealGiocatoriTotali = num;

  for(i = ZERO; i < file->numRealGiocatoriTotali; i++)
  {
    printf("Inserire il nome del Giocatore num.%d: ", i + UNO);
    scanf(" %[^\n]s", nome);

    file->giocatori[i] = initGiocatore(NEG_VAL,nome);
  }
}

void assegnaGiocatori(GameFile *file)
{
  int i, j, num;
  bool scelta, found;

  file->numRealGiocatoriAttuali = ZERO;

  for(i = ZERO; i < file->numRealGiocatoriTotali; i++)
  {
    system("cls");
    stampaGiocatore(file->giocatori[i]);
    printf("Selezionare questo giocatore?");
    scelta = yesOrNo();

    if(scelta)
    {
      do
      {
        found = false;

        printf("Scegliere l'ID del giocatore [%d - %d]: ", ZERO, file->numGiocatoriTotali - UNO);
        scanf("%d",&num);
        printf("\n");

        if(num < ZERO || num > file->numGiocatoriTotali - UNO)
          printf("Scegliere un numero tra %d e %d\n\n", ZERO, file->numGiocatoriTotali - UNO);

        for(j = ZERO; j < file->numRealGiocatoriTotali; j++)
        {
          if(file->giocatori[j].idGiocatore == num && num != NEG_VAL)
          {
            found = true;
            printf("ID gia' inserito\n\n");
          }
        }
      } while(num < ZERO || num > file->numGiocatoriTotali - UNO || found == true);

      file->giocatori[i].idGiocatore = num;
      file->numRealGiocatoriAttuali += UNO;
    }
  }
}

Gruppo* creaGruppiIniziali(GameFile *file, int numGruppi)
{
  Gruppo *gruppi;
  int i, resto, index, *alreadyIns;

  gruppi = (Gruppo*) malloc(numGruppi * sizeof(Gruppo));
  alreadyIns = (int*) calloc(numGruppi,sizeof(int));

  resto = file->numGiocatoriTotali % numGruppi;

  for (i = ZERO; i < numGruppi; i++)
  {
    if(i < resto)
      gruppi[i].numGiocatori = (file->numGiocatoriTotali / numGruppi) + UNO;
    else
      gruppi[i].numGiocatori = (file->numGiocatoriTotali / numGruppi);

    gruppi[i].giocatori = (int *) malloc(gruppi[i].numGiocatori * sizeof(int));
  }

  for (i = ZERO; i < file->numGiocatoriTotali; i++)
  {
    do
      index = rand() % numGruppi;
    while (alreadyIns[index] >= gruppi[index].numGiocatori);

    gruppi[index].giocatori[alreadyIns[index]] = i;
    alreadyIns[index]++;
  }

  free(alreadyIns);

  return gruppi;
}

int numGiocatori()
{
  int size;

  do
  {
    printf("Inserire il numero di giocatori (almeno %d): ", MIN_GIOCATORI);
    scanf("%d", &size);
    printf("\n");

    if(size < MIN_GIOCATORI)
      printf("Inserire un numero maggiore o uguale a %d\n\n", MIN_GIOCATORI);
  } while(size < MIN_GIOCATORI);

  return size;
}

void abilitaGiocatori(GameFile *file)
{
  int i;

  file->inGioco = malloc(sizeof(int) * file->numGiocatoriTotali);

  for(i = ZERO; i < file->numGiocatoriTotali; i++)
    file->inGioco[i] = ALIVE;
}

void inizio(GameFile *file)
{
  Gruppo *gruppi;
  int numGruppi, size, ctrlGiocatori, i, *winners;

  system("cls");
  size = numGiocatori();

  do
  {
    printf("Inserire il numero di giocatori che si vogliono creare: ");
    scanf("%d", &ctrlGiocatori);
    printf("\n");

    if(ctrlGiocatori > size)
      printf("Inserire un numero minore o uguale a %d\n\n", size);
    else if(ctrlGiocatori < ZERO)
      printf("Inserire un numero corretto (%d - %d)\n\n", ZERO, size);
  } while(ctrlGiocatori > size || ctrlGiocatori < ZERO);

  file->numGiocatoriTotali = size;
  abilitaGiocatori(file);
  file->numRealGiocatoriAttuali = file->numRealGiocatoriTotali = ctrlGiocatori;

  initInGioco(file);
  if(ctrlGiocatori > ZERO)
  {
    creaGiocatori(file,ctrlGiocatori);
    assegnaGiocatori(file);
  }

  system("cls");
  numGruppi = numGruppiPlayers(size);
  gruppi = creaGruppiIniziali(file, numGruppi);
  printf("GRUPPI INIZIALI\n\n");
  printGruppi(gruppi, numGruppi);
  enter();

  winners = malloc(sizeof(int) * numGruppi);

  for(i = ZERO; i < numGruppi; i++)
  {
    system("cls");
    winners[i] = scrematura(file, gruppi[i]);
  }

  free(gruppi);
}