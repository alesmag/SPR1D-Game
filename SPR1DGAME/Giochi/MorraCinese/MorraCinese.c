#include "MorraCinese.h"

void sceltaCpuMorraCinese(int *scelta, Gruppo gruppo, int i)
{
  scelta[i] = rand() % TRE;

  if(scelta[i] == CARTA)
    printf("Giocatore n.%d ha scelto Carta\n\n", gruppo.giocatori[i]);
  else if(scelta[i] == FORBICI)
    printf("Giocatore n.%d ha scelto Forbici\n\n", gruppo.giocatori[i]);
  else if(scelta[i] == SASSO)
    printf("Giocatore n.%d ha scelto Sasso\n\n", gruppo.giocatori[i]);
}

void sceltaGiocatoreMorraCinese(int *scelta, Gruppo gruppo, int i)
{
  do
  {
    printf("Scegli cosa giocare: \n%d: Carta \n%d: Forbici \n%d: Sasso \n\nScelta:", UNO, DUE, TRE);
    scanf("%d", &scelta[i]);
    printf("\n");
    scelta[i]--;

    if (scelta[i] < CARTA || scelta[i] > SASSO)
      printf("Inserire un numero compreso tra %d e %d\n\n", CARTA, SASSO);

  } while (scelta[i] < CARTA || scelta[i] > SASSO);
}

int morraCinese(GameFile *file, Gruppo gruppo)
{
  int scelta[DUE_PLAYER], i = ZERO, winner = NEG_VAL, num = ZERO;

  system("clear");
  printf("----- MORRA CINESE -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    while(winner == NEG_VAL)
    {
      for(i = ZERO; i < DUE_PLAYER; i++)
      {
        printf("\n--- Turno Giocatore n.%d ---\n\n", gruppo.giocatori[i]);

        if(isCpu(*file, gruppo.giocatori[i]) == true)
          sceltaCpuMorraCinese(scelta, gruppo, i);

        else
          sceltaGiocatoreMorraCinese(scelta, gruppo, i);
      }

      if((scelta[PLAYERUNO] == CARTA && scelta[PLAYERDUE] == SASSO) || (scelta[PLAYERUNO] == FORBICI && scelta[PLAYERDUE] == CARTA) || (scelta[PLAYERUNO] == SASSO && scelta[PLAYERDUE] == FORBICI))
        winner = gruppo.giocatori[PLAYERUNO];

      else if((scelta[PLAYERDUE] == CARTA && scelta[PLAYERUNO] == SASSO) || (scelta[PLAYERDUE] == FORBICI && scelta[PLAYERUNO] == CARTA) || (scelta[PLAYERDUE] == SASSO && scelta[PLAYERUNO] == FORBICI))
        winner = gruppo.giocatori[PLAYERDUE];

      else if(scelta[PLAYERUNO] == scelta[PLAYERDUE])
        printf("\nPAREGGIO\n\n\n");
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