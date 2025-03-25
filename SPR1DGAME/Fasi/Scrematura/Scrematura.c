#include "Scrematura.h"

int sceltaCpu(int numMin, int numMag)
{
  int num;

  if(numMag==numMin)
    num=numMin;
  else
    num = numMin + rand() % (numMag - numMin) + UNO;

  printf("Ha scelto: %d\n", num);

  return num;
}

int sceltaGiocatore(int numMin, int numMag)
{
  int num;

  do
  {
    printf("Inserire un numero [%d - %d]: ", numMin, numMag);
    scanf("%d", &num);

    if(num < numMin || num > numMag)
      printf("Numero fuori dal range\n\n");
  } while(num < numMin || num > numMag);

  return num;
}

void initVett(Gruppo gruppo, int *numMin, int *numMag)
{
  int i;

  for(i = 0; i < gruppo.numGiocatori; i++)
    numMin[i] = ZERO;

  for(i = 0; i < gruppo.numGiocatori; i++)
    numMag[i] = MAX_NUM;
}

int isVinta(Gruppo gruppo, int scelta, int num, int *numMin, int *numMag, int i, bool cond)
{
  if((scelta == num) || (numMin[i] == numMag[i]))
  {
    printf("HAI INDOVINATO\n\n\n", gruppo.giocatori[i]);
    return gruppo.giocatori[i];
  }

  else if(scelta < num)
  {
    printf("Numero troppo piccolo, riprova\n\n");
    numMin[i] = scelta + UNO;
  }

  else if(scelta > num)
  {
    printf("Numero troppo grande, riprova\n\n");
    numMag[i] = scelta - UNO;
  }

  if(cond == true)
    sleep(UNO);

  return NEG_VAL;
}

int scrematura(GameFile *file, Gruppo gruppo)
{
  int num, winner = NEG_VAL, i, numMin[gruppo.numGiocatori], numMag[gruppo.numGiocatori], scelta;
  bool cond;

  system("clear");
  printf("----- INDOVINA IL NUMERO -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    initVett(gruppo, numMin, numMag);
    num = rand() % MAX_NUM;

    while(winner == NEG_VAL)
    {
      for(i = ZERO; i < gruppo.numGiocatori; i++)
      {
        printf("\n--- Turno Giocatore n.%d ---\n\n", gruppo.giocatori[i]);

        if(isCpu(*file, gruppo.giocatori[i]) == true)
        {
          cond = false;
          scelta = sceltaCpu(numMin[i], numMag[i]);
        }

        else
        {
          cond = true;
          scelta = sceltaGiocatore(numMin[i], numMag[i]);
        }

        winner = isVinta(gruppo, scelta, num, numMin, numMag, i, cond);

        if(winner != NEG_VAL)
          i = gruppo.numGiocatori;
      }
    }
  }

  if(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali)!=NEG_VAL)
    if(isPlayerInGroup(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali),gruppo.giocatori,gruppo.numGiocatori)!=NEG_VAL)
      winner = gruppo.giocatori[isPlayerInGroup(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali),gruppo.giocatori,gruppo.numGiocatori)];

  printf("HAI VINTO Giocatore n.%d\n\n", winner);
  enter();

  aggiornaStats(file, gruppo, winner, false);
  uccidiPlayer(file, gruppo, winner);

  return winner;
}