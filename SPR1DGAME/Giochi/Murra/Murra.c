#include "Murra.h"

int murra(GameFile *file, Gruppo gruppo)
{
  int sceltaNum[DUE_PLAYER], sceltaSum[DUE_PLAYER], winner = NEG_VAL, num, i, somma;

  system("clear");
  printf("----- MURRA -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    while (winner == NEG_VAL)
    {
      for (i = ZERO; i < DUE_PLAYER; i++)
      {
        printf("\n--- Turno Giocatore n.%d ---\n\n", gruppo.giocatori[i]);

        if(isCpu(*file, gruppo.giocatori[i]) == true)
        {
          sceltaNum[i] = UNO + rand() % CINQUE;
          sceltaSum[i] = DUE + rand() % (DIECI - DUE) + UNO;
          printf("Ha scelto %d come numero e %d come somma\n\n", sceltaNum[i], sceltaSum[i]);
        }

        else
        {
          do
          {
            printf("Scegli un numero compreso tra %d e %d:", UNO, CINQUE);
            scanf("%d", &sceltaNum[i]);
            fflush(stdin);
            printf("\n");

            if (sceltaNum[i] < UNO || sceltaNum[i] > CINQUE)
              printf("Numero fuori dal range\n\n");
          } while (sceltaNum[i] < UNO || sceltaNum[i] > CINQUE);

          do
          {
            printf("Scegli un numero compreso tra %d e %d:", DUE, DIECI);
            scanf("%d", &sceltaSum[i]);
            printf("\n");

            if (sceltaSum[i] < DUE || sceltaSum[i] > DIECI)
              printf("Numero fuori dal range\n\n");
          } while (sceltaSum[i] < DUE || sceltaSum[i] > DIECI);
        }
      }

      somma = sceltaNum[PLAYERUNO] + sceltaNum[PLAYERDUE];

      if(somma == sceltaSum[PLAYERUNO] && somma == sceltaSum[PLAYERDUE])
        printf("PAREGGIO\n\n");

      else if (somma == sceltaSum[PLAYERUNO])
        winner = gruppo.giocatori[PLAYERUNO];

      else if (somma == sceltaSum[PLAYERDUE])
        winner = gruppo.giocatori[PLAYERDUE];
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