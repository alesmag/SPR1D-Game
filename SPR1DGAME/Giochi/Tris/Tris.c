#include "Tris.h"

void loadMatrix(int tris[TRE][TRE])
{
  int counter = NOVE, i, j;

  for(i = ZERO; i < TRE; i++)
    for(j = DUE; j >= ZERO; j--)
      tris[i][j] = counter--;
}

void showMatrix(int tris[TRE][TRE])
{
  int i, j;

  printf("\n");

  for(i = ZERO; i < TRE; i++)
  {
    for(j = ZERO; j < TRE; j++)
    {
      if(tris[i][j] == PLAYER_X)
        printf(" X");

      else if(tris[i][j] == PLAYER_O)
        printf(" O");

      else
        printf(" %d",tris[i][j]);

      if(j < DUE)
        printf(" |");

      if(j == DUE)
        printf("\n");
    }

    if(i < DUE)
      printf("-----------\n");
  }

  printf("\n\n");
}

int findPos(int tris[TRE][TRE], int cell[DUE], int pos)
{
  int find = ZERO, i, j;

  for(i = ZERO; i < TRE; i++)
  {
    for(j = ZERO; j < TRE; j++)
    {
      if(tris[i][j] == pos)
      {
        cell[ZERO] = i;
        cell[UNO] = j;
        find = UNO;
      }
    }
  }

  return find;
}

int isVintaTris(Gruppo gruppo, int tris[TRE][TRE], int symbol)
{
  int x, y, winner = NEG_VAL;

  //controllo se ci sono tris nelle colonne
  for(x = ZERO; x < TRE; x++)
    if(tris[x][ZERO] == symbol && tris[x][ZERO] == tris[x][UNO] && tris[x][UNO] == tris[x][DUE])
      winner = symbol;

  //controllo se ci sono tris nelle righe
  for(y = ZERO; y < TRE; y++)
    if (tris[ZERO][y]==symbol && tris[ZERO][y]==tris[UNO][y] && tris[UNO][y]==tris[DUE][y])
      winner = symbol;

  //controllo se ci sono tris nelle diagonali
  if(tris[ZERO][ZERO] == symbol && tris[ZERO][ZERO] == tris[UNO][UNO] && tris[UNO][UNO] == tris[DUE][DUE])
    winner = symbol;

  else if (tris[ZERO][DUE] == symbol && tris[ZERO][DUE] == tris[UNO][UNO] && tris[UNO][UNO] == tris[DUE][ZERO])
    winner = symbol;

  if(winner == PLAYER_X)
    winner = gruppo.giocatori[PLAYERUNO];
  else if(winner == PLAYER_O)
    winner = gruppo.giocatori[PLAYERDUE];

  return winner;
}

int setMatrix(int tris[TRE][TRE], int cell[DUE], int pos, int symbol)
{
  int set = ZERO;

  if(findPos(tris, cell, pos) == UNO)
  {
    tris[cell[ZERO]][cell[UNO]] = symbol;
    set = UNO;
  }

  else
    printf("La posizione indicata non e' disponibile!\n\n");

  return set;
}

bool isTrisPieno(int tris[TRE][TRE])
{
  int i, j;

  for(i = ZERO; i < TRE; i++)
    for(j = ZERO; j < TRE; j++)
      if(tris[i][j] != PLAYER_X && tris[i][j] != PLAYER_O)
        return false;

  return true;
}

int tris(GameFile *file, Gruppo gruppo)
{
  int symbol, tris[TRE][TRE], winner = NEG_VAL, hand, pos, num, cell[DUE];

  system("clear");
  printf("----- TRIS -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    loadMatrix(tris);

    if(gruppo.giocatori[PLAYERUNO] < gruppo.giocatori[PLAYERDUE])
      hand = UNO;
    else
      hand = DUE;

    while (winner == NEG_VAL)
    {
      if(isTrisPieno(tris) == true)
      {
        printf("\nPAREGGIO\n\n");
        loadMatrix(tris);
      }

      if(hand == UNO)
      {
        symbol = PLAYER_X;

        showMatrix(tris);

        if(isCpu(*file, gruppo.giocatori[PLAYERUNO]) == true)
        {
          do
          {
            pos = UNO + rand() % NOVE;
            printf("Scelta Giocatore n.%d (X): %d", gruppo.giocatori[PLAYERUNO], pos);
            printf("\n\n");
          }
          while(!setMatrix(tris, cell, pos, symbol));
        }

        else
        {
          do
          {
            printf("Scelta Giocatore n.%d (X): ", gruppo.giocatori[PLAYERUNO]);
            scanf("%d", &pos);
            printf("\n\n");
          } while(!setMatrix(tris, cell, pos, symbol));
        }

        hand = DUE;
      }

      else
      {
        symbol = PLAYER_O;

        showMatrix(tris);

        if(isCpu(*file, gruppo.giocatori[PLAYERDUE]) == true)
        {
          do
          {
            pos = UNO + rand() % NOVE;
            printf("Scelta Giocatore n.%d (O): %d", gruppo.giocatori[PLAYERDUE], pos);
            printf("\n\n");
          }
          while(!setMatrix(tris, cell, pos, symbol));
        }

        else
        {
          do
          {
            printf("Scelta Giocatore n.%d (O): ", gruppo.giocatori[PLAYERDUE]);
            scanf("%d", &pos);
            printf("\n\n");
          } while(!setMatrix(tris, cell, pos, symbol));
        }

        hand = UNO;
      }

      winner = isVintaTris(gruppo, tris, symbol);
    }

    showMatrix(tris);
  }

  if(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali)!=NEG_VAL)
    if(isPlayerInGroup(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali),gruppo.giocatori,gruppo.numGiocatori)!=NEG_VAL)
      winner = gruppo.giocatori[isPlayerInGroup(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali),gruppo.giocatori,gruppo.numGiocatori)];

  printf("\nHAI VINTO Giocatore n.%d\n\n", winner);
  enter();

  aggiornaStats(file, gruppo, winner, false);
  uccidiPlayer(file, gruppo, winner);

  return 0;
}