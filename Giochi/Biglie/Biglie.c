#include "Biglie.h"

void scommessaGiocatore(int *numBiglie, int *biglieScomm, int j)
{
  do
  {
    printf("Scegli il numero di biglie da scommettere [%d - %d]: ", UNO, numBiglie[j]);
    scanf("%d", &biglieScomm[j]);
    printf("\n\n");

    if(biglieScomm[j] < UNO || biglieScomm[j] > numBiglie[j])
      printf("Scegli un numero compreso tra %d e %d\n\n", UNO, numBiglie[j]);
  } while(biglieScomm[j] < UNO || biglieScomm[j] > numBiglie[j]);
}

void scommessaCpu(int *numBiglie, int *biglieScomm, int j)
{
  biglieScomm[j] = UNO + rand() % numBiglie[j];
  printf("Ha scommesso\n\n", biglieScomm[j]);
}

void pdGiocatore(int *pd, int i)
{
  do
  {
    printf("Scegli se l'altro giocatore ha scommesso un numero Pari o Dispari di biglie. \n%d: Pari \n%d: Dispari \nScelta: ", UNO, DUE);
    scanf("%d", &pd[i]);
    printf("\n\n");

    if(pd[i] < UNO || pd[i] > DUE)
      printf("Scegliere %d se Pari o %d se Dispari\n\n", UNO, DUE);
  } while(pd[i] < UNO || pd[i] > DUE);
}

void pdCpu(int *pd, int i)
{
  pd[i] = UNO + rand() % DUE;

  if(pd[i] == UNO)
    printf("Sta pensando ad un numero Pari\n\n");
  else
    printf("Sta pensando ad un numero Dispari\n\n");
}

void distribuzioneBiglie(int *biglieScomm, int *numBiglie, int *pd, int i)
{
  if(((biglieScomm[(i + UNO) % DUE_PLAYER] % DUE == ZERO) && pd[i] == UNO) || (biglieScomm[(i + UNO) % DUE_PLAYER] % DUE != ZERO) && (pd[i] == DUE))
  {
    printf("Hai indovinato\n");
    numBiglie[i] += biglieScomm[(i + UNO) % DUE_PLAYER];
    numBiglie[(i + UNO) % DUE_PLAYER] -= biglieScomm[(i + UNO) % DUE_PLAYER];
    printf("Hai guadagnato %d biglie\n\n", biglieScomm[(i + UNO) % DUE_PLAYER]);
  }

  else if(((biglieScomm[(i + UNO) % DUE_PLAYER] % DUE == ZERO) && pd[i] == DUE) || (biglieScomm[(i + UNO) % DUE_PLAYER] % DUE != ZERO) && (pd[i] == UNO))
  {
    printf("Non hai indovinato\n");
    numBiglie[(i + UNO) % DUE_PLAYER] += biglieScomm[i];
    numBiglie[i] -= biglieScomm[i];
    printf("Hai perso %d biglie\n\n", biglieScomm[i]);
  }
}

int isVintaBiglie(int *numBiglie, Gruppo gruppo, int i)
{
  int winner = NEG_VAL;

  if(numBiglie[i] < UNO)
    winner = gruppo.giocatori[(i + UNO) % DUE_PLAYER];

  else if(numBiglie[(i + UNO) % DUE_PLAYER] < UNO)
    winner = gruppo.giocatori[i];

  return winner;
}

int biglie(GameFile *file, Gruppo gruppo)
{
  int winner = NEG_VAL, num, i = ZERO, j, numBiglie[DUE_PLAYER] = {START_NUM_BIGLIE, START_NUM_BIGLIE}, biglieScomm[DUE_PLAYER] = {}, pd[DUE_PLAYER] = {};

  system("cls");
  printf("----- BIGLIE -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    while(winner == NEG_VAL)
    {
      j = ZERO;
      while(j < DUE)
      {
        printf("\n--- Turno Giocatore n.%d ---\n\n", gruppo.giocatori[j]);

        if(isCpu(*file, gruppo.giocatori[j]) == true)
          scommessaCpu(numBiglie, biglieScomm, j);

        else
          scommessaGiocatore(numBiglie, biglieScomm, j);

        j++;
      }

      printf("\n--- Turno Giocatore n.%d ---\n\n", gruppo.giocatori[i]);

      if(isCpu(*file, gruppo.giocatori[i]) == true)
        pdCpu(pd, i);

      else
        pdGiocatore(pd, i);

      distribuzioneBiglie(biglieScomm, numBiglie, pd, i);
      winner = isVintaBiglie(numBiglie, gruppo, i);
      i = (i + UNO) % DUE_PLAYER;
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