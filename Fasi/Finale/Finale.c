#include "Finale.h"

Gruppo* creaGruppoFinale(GameFile *file, int numGruppi)
{
  Gruppo *gruppi;
  int i, resto, index, *alreadyIns, *idAlive;

  gruppi = (Gruppo *) malloc(numGruppi * sizeof(Gruppo));
  alreadyIns = (int *) calloc(numGruppi,sizeof(int));
  idAlive = (int *) malloc(sizeof (int)*countNumAlive(*file));

  alivePlayers(*file,idAlive);
  resto = countNumAlive(*file) % numGruppi;

  for (i = ZERO; i < numGruppi; i++)
  {
    if(i < resto)
      gruppi[i].numGiocatori = (countNumAlive(*file) / numGruppi) + UNO;
    else
      gruppi[i].numGiocatori = (countNumAlive(*file) / numGruppi);

    gruppi[i].giocatori = (int *) malloc(gruppi[i].numGiocatori * sizeof(int));
  }

  for (i = ZERO; i < countNumAlive(*file); i++)
  {
    do
      index = rand() % numGruppi;
    while (alreadyIns[index] >= gruppi[index].numGiocatori);

    gruppi[index].giocatori[alreadyIns[index]] = idAlive[i];
    alreadyIns[index]++;
  }

  free(alreadyIns);

  return gruppi;
}

void printGruppoFinale(Gruppo gruppo)
{
  int i, j;

  for(i = 0; i < UNO; i++)
  {
    printf("GRUPPO FINALE\n");

    for(j = 0; j < gruppo.numGiocatori; j++)
      printf("ID: %d\n", gruppo.giocatori[j]);
    printf("\n");
  }
}

void riempiMazzo(Carta *mazzo)
{
  int i;

  for (i = ZERO; i < CARTE; i++)
  {
    mazzo[i].faccia = i % FACCE;
    mazzo[i].seme = i / FACCE;
  }
}

void mischia(Carta *mazzo)
{
  Carta temp;
  int i, j;

  for (i = CARTE-UNO; i > ZERO; i--)
  {
    j = rand() % (i+UNO);
    temp = mazzo[i];
    mazzo[i] = mazzo[j];
    mazzo[j] = temp;
  }
}

int valCarta(Faccia faccia)
{
  if(faccia == Fante || faccia == Re || faccia == Regina)
      return VAL_FIGURE;
  else
    return faccia + UNO;
}

char *stampaFaccia(Faccia facciaCarta)
{
  switch(facciaCarta)
  {
    case Asso:
      return "Asso";
    case Due:
      return "Due";
    case Tre:
      return "Tre";
    case Quattro:
      return "Quattro";
    case Cinque:
      return "Cinque";
    case Sei:
      return "Sei";
    case Sette:
      return "Sette";
    case Otto:
      return "Otto";
    case Nove:
      return "Nove";
    case Dieci:
      return "Dieci";
    case Regina:
      return "Regina";
    case Re:
      return "Re";
    case Fante:
      return "Fante";
    default:
      return "";
  }
}

char *stampaSeme(Seme seme)
{
  switch (seme)
  {
    case Cuori:
      return "Cuori";
    case Quadri:
      return "Quadri";
    case Picche:
      return "Picche";
    case Fiori:
      return "Fiori";
    default:
      return "";
  }
}

void getCarta(ManoGiocatore *mazzoGiocatore, Carta *mazzo, int *cartaAtt)
{
  bool scelta = false;

  printf("\nOttenuto: %s di %s", stampaFaccia(mazzo[*cartaAtt].faccia), stampaSeme(mazzo[*cartaAtt].seme));

  if(valCarta(mazzo[*cartaAtt].faccia) == Asso + UNO)
  {
    if(mazzoGiocatore->isBot != true)
    {
      printf("\nVuoi che il suo valore sia undici?\n");
      scelta = yesOrNo();
    }

    else
      if(mazzoGiocatore->valTot < VALORE_TOTALE_ASSO_MAX)
        scelta = true;

    if(scelta == false)
      mazzoGiocatore->valTot += VALORE_ASSO_MIN;
    else
      mazzoGiocatore->valTot += VALORE_ASSO_MAX;
  }

  else
    mazzoGiocatore->valTot += valCarta(mazzo[*cartaAtt].faccia);

  *cartaAtt += UNO;
  printf("\nPunti totali: %d\n", mazzoGiocatore->valTot);
}

void initMazzoGiocatore(ManoGiocatore *mazzoGiocatore, GameFile file, int id)
{
  mazzoGiocatore->valTot = ZERO;

  if(isCpu(file,id) == true)
    mazzoGiocatore->isBot = true;
  else
    mazzoGiocatore->isBot = false;
}

bool isBlackjack(int totale)
{
  if(totale == BLACKJACK)
    return true;

  return false;
}

bool hasSbancato(int totale)
{
  if(totale > BLACKJACK)
    return true;

  return false;
}

int isWin(ManoGiocatore *mazzoGiocatore, Gruppo gruppo, bool fine)
{
  int winner = NEG_VAL;

  if(isBlackjack(mazzoGiocatore[ZERO].valTot)&&isBlackjack(mazzoGiocatore[UNO].valTot))
  {
      printf("\nPareggio\n\n");
      return PARITA;
  }
  else if(isBlackjack(mazzoGiocatore[ZERO].valTot)&&fine!=true)
      return gruppo.giocatori[ZERO];

  else if(isBlackjack(mazzoGiocatore[UNO].valTot))
      return gruppo.giocatori[UNO];

  if(hasSbancato(mazzoGiocatore[ZERO].valTot) && hasSbancato(mazzoGiocatore[UNO].valTot))
  {
    printf("\nPareggio\n\n");
    return PARITA;
  }

  else if(hasSbancato(mazzoGiocatore[ZERO].valTot))
    return gruppo.giocatori[UNO];

  else if(hasSbancato(mazzoGiocatore[UNO].valTot))
    return gruppo.giocatori[ZERO];

  if(fine == true)
  {
    if(mazzoGiocatore[ZERO].valTot > mazzoGiocatore[UNO].valTot)
      return gruppo.giocatori[ZERO];

    else if((mazzoGiocatore[ZERO].valTot < mazzoGiocatore[UNO].valTot))
      return gruppo.giocatori[UNO];

    else if(mazzoGiocatore[ZERO].valTot == mazzoGiocatore[UNO].valTot)
    {
      printf("\nPareggio\n\n");
      return PARITA;
    }
  }

  return winner;
}

void start(GameFile file, ManoGiocatore *mazzoGiocatore, Carta *mazzo, int *cartaAtt, Gruppo gruppi)
{
  int i;

  for(i = ZERO; i < DUE; i++)
  {
    printf("\n\nGiocatore n.%d: Prime due carte\n",gruppi.giocatori[i]);
    initMazzoGiocatore(&mazzoGiocatore[i],file,gruppi.giocatori[i]);
    getCarta(&mazzoGiocatore[i],mazzo,cartaAtt);
    getCarta(&mazzoGiocatore[i],mazzo,cartaAtt);
  }
}

int blackjack(GameFile *file, Gruppo gruppo)
{
  int winner = NEG_VAL, num, i, cartaAtt = ZERO;
  bool fine = false, scelta = false;
  ManoGiocatore mazzoGiocatore[DUE];
  Carta mazzo[CARTE];

  system("cls");
  printf("----- BLACKJACK -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    riempiMazzo(mazzo);

    while(winner == NEG_VAL)
    {
      mischia(mazzo);

      start(*file, mazzoGiocatore, mazzo, &cartaAtt, gruppo);
      winner = isWin(mazzoGiocatore, gruppo, fine);

      if(winner == NEG_VAL && winner != PARITA)
      {
        for(i = ZERO; i < DUE_PLAYER; i++)
        {
          printf("\n\n\n--- Turno Giocatore n.%d ---\n",gruppo.giocatori[i]);

          if(isCpu(*file,gruppo.giocatori[i]))
          {
            while(mazzoGiocatore[i].valTot < VALORE_MAX_RISCHIO && winner == NEG_VAL)
            {
              printf("\nPesca una carta");
              getCarta(&mazzoGiocatore[i], mazzo, &cartaAtt);
              winner = isWin(mazzoGiocatore, gruppo, false);
            }
          }

          else
          {
            do
            {
              printf("\nPescare un'altra carta?\n");
              scelta = yesOrNo();

              if(scelta == true)
                getCarta(&mazzoGiocatore[i], mazzo, &cartaAtt);

              winner = isWin(mazzoGiocatore, gruppo, false);
            } while(scelta == true && winner == NEG_VAL);
          }

          winner = isWin(mazzoGiocatore, gruppo, false);

          if(winner != NEG_VAL)
            i = DUE_PLAYER;
        }

        winner = isWin(mazzoGiocatore, gruppo, true);
      }

      if(winner == PARITA)
        winner = NEG_VAL;
    }
  }

  if(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali)!=NEG_VAL)
    if(isPlayerInGroup(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali),gruppo.giocatori,gruppo.numGiocatori)!=NEG_VAL)
      winner = gruppo.giocatori[isPlayerInGroup(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali),gruppo.giocatori,gruppo.numGiocatori)];

  printf("\n\n\nHAI VINTO Giocatore n.%d\n\n", winner);
  enter();

  aggiornaStats(file, gruppo, winner, true);
  uccidiPlayer(file, gruppo, winner);
  return winner;
}

void finale(GameFile *file)
{
  Gruppo *gruppi;
  int winner;

  gruppi = creaGruppoFinale(file, UNO);
  system("cls");
  printGruppoFinale(gruppi[ZERO]);
  enter();

  winner = blackjack(file, gruppi[ZERO]);

  free(gruppi);
}