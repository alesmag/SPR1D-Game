#include "PariDispari.h"

int pariDispari(GameFile *file, Gruppo gruppo)
{
  int sceltaPD[DUE_PLAYER], sceltaNum[DUE_PLAYER], winner = NEG_VAL, i, num, somma;

  system("cls");
  printf("----- PARI O DISPARI -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    while (winner == NEG_VAL)
    {
      if(isCpu(*file, gruppo.giocatori[PLAYERUNO]) == true)
      {
        sceltaPD[PLAYERUNO] = UNO + rand() % DUE;

        if(sceltaPD[PLAYERUNO] == UNO)
          printf("Scelta Giocatore n.%d: Pari\n\n", gruppo.giocatori[PLAYERUNO]);
        else
          printf("Scelta Giocatore n.%d: Dispari\n\n", gruppo.giocatori[PLAYERUNO]);
      }

      else
      {
        do
        {
          printf("Giocatore n.%d scegli se essere pari o dispari \n%d: Pari \n%d: Dispari \nScelta: ", gruppo.giocatori[PLAYERUNO], UNO, DUE);
          scanf("%d", &sceltaPD[PLAYERUNO]);
          printf("\n");

          if (sceltaPD[PLAYERUNO] < UNO || sceltaPD[PLAYERUNO] > DUE)
            printf("Numero fuori dal range\n\n");
        } while (sceltaPD[PLAYERUNO] < UNO || sceltaPD[PLAYERUNO] > DUE);
      }

      if (sceltaPD[PLAYERUNO] == UNO)
        sceltaPD[PLAYERDUE] = DUE;
      else
        sceltaPD[PLAYERDUE] = UNO;

      for (i = 0; i < DUE_PLAYER; i++)
      {
        printf("\n--- Turno Giocatore n.%d ---\n\n", gruppo.giocatori[i]);

        if(isCpu(*file, gruppo.giocatori[i]) == true)
        {
          sceltaNum[i] = rand() % SEI;
          printf("Scelta Giocatore n.%d: %d\n\n", gruppo.giocatori[i], sceltaNum[i]);
        }

        else
        {
          do
          {
            printf("Scegli un numero compreso tra %d e %d: ", ZERO, CINQUE);
            scanf("%d", &sceltaNum[i]);
            printf("\n");

            if (sceltaNum[i] < ZERO || sceltaNum[i] > CINQUE)
              printf("Numero fuori dal range\n\n");
          } while (sceltaNum[i] < ZERO || sceltaNum[i] > CINQUE);
        }
      }

      somma = sceltaNum[PLAYERUNO] + sceltaNum[PLAYERDUE];

      if (((somma % DUE == ZERO) && (sceltaPD[PLAYERUNO] == UNO)) ||
          ((somma % DUE == ZERO) && (sceltaPD[PLAYERDUE] == DUE)) ||
          ((somma % DUE != ZERO) && (sceltaPD[PLAYERDUE] == UNO)) ||
          ((somma % DUE != ZERO) && (sceltaPD[PLAYERUNO] == DUE)))
        winner = gruppo.giocatori[PLAYERUNO];

      else if (((somma % DUE == ZERO) && (sceltaPD[PLAYERDUE] == UNO)) ||
               ((somma % DUE == ZERO) && (sceltaPD[PLAYERUNO] == DUE)) ||
               ((somma % DUE != ZERO) && (sceltaPD[PLAYERUNO] == UNO)) ||
               ((somma % DUE != ZERO) && (sceltaPD[PLAYERDUE] == DUE)))
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