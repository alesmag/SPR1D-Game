#include "Dadi.h"

int lanciaDadi(GameFile *file, Gruppo gruppo, int i)
{
  int somma, num1, num2;

  if(isCpu(*file, gruppo.giocatori[i]) == false)
  {
    printf("Premere INVIO per lanciare i dadi\n\n");
    fflush(stdin);
    fflush(stdout);
    getchar();
  }

  num1 = UNO + rand() % SEI;
  num2 = UNO + rand() % SEI;
  somma = num1 + num2;

  printf("Primo dado: %d \nSecondo dado: %d \nSomma dei dadi: %d\n\n", num1, num2, somma);

  return somma;
}

int dadi(GameFile *file, Gruppo gruppo)
{
  int winner = NEG_VAL, i, num, somme[DUE_PLAYER][DUE] = {};

  system("cls");
  printf("----- DADI -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    i = rand() % DUE_PLAYER;

    while(winner == NEG_VAL)
    {
      printf("\n--- Turno Giocatore n.%d ---\n\n", gruppo.giocatori[i]);

      somme[i][ZERO] = somme[i][UNO];

      if(isCpu(*file, gruppo.giocatori[i]) == true)
        somme[i][UNO] = lanciaDadi(file, gruppo, i);
      else
        somme[i][UNO] = lanciaDadi(file, gruppo, i);

      if(somme[i][ZERO] > somme[i][UNO])
        winner = gruppo.giocatori[(i + UNO) % DUE_PLAYER];

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