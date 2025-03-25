#include "Svolgimento.h"

void printGioco(giochi gioco)
{
  switch (gioco)
  {
    case PARIDISPARI:
      printf("PARI O DISPARI\n");
      break;

    case DADI:
      printf("DADI\n");
      break;

    case MORRACINESE:
      printf("MORRA CINESE\n");
      break;

    case MURRA:
      printf("MURRA\n");
      break;

    case TRIS:
      printf("TRIS\n");
      break;

    case BIGLIE:
      printf("BIGLIE\n");
      break;

      case IMPICCATO:
        printf("IMPICCATO\n");
        break;

    default:
      exit(NEG_VAL);
  }
}

Gruppo* creaGruppiSvolgimento(GameFile *file, int numGruppi)
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

void svolgimento(GameFile *file)
{
  if(countNumAlive(*file) > DUE)
  {
    int numGruppi, i;
    Gruppo *gruppi;
    giochi gioco;

    srand(time(NULL));

    do
    {
      system("clear");

      if(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali) == NEG_VAL)
      {
        if (countNumAlive(*file) > QUATTRO)
          gioco = PARIDISPARI + rand() % IMPICCATO;
        else
          gioco = PARIDISPARI + rand() % BIGLIE;
      }

      else
      {
        printf("%s, scegli il gioco\n\n", NAME_IMMORTAL_PLAYER);
        printf("%d: Pari o Dispari \n%d: Dadi \n%d: Morra Cinese \n%d: Murra \n%d: Tris \n%d: Biglie\n", PARIDISPARI+UNO, DADI+UNO, MORRACINESE+UNO, MURRA+UNO, TRIS+UNO, BIGLIE+UNO);

        if (countNumAlive(*file) > QUATTRO)
        {
          printf("%d: Impiccato\n", IMPICCATO+UNO);

          do
          {
            printf("\nScelta: ");
            scanf("%d", &gioco);
            gioco -= UNO;
          }
          while(gioco < PARIDISPARI || gioco > IMPICCATO);
        }

        else
        {
          do
          {
            printf("\nScelta: ");
            scanf("%d", &gioco);
            gioco -= UNO;
          }
          while(gioco < PARIDISPARI || gioco > BIGLIE);
        }
      }

      system("clear");

      printf("GIOCO: ");
      printGioco(gioco);

      if (gioco <= BIGLIE)
        numGruppi = countNumAlive(*file) / DUE;
      else if(gioco == IMPICCATO)
        numGruppi = numGruppiPlayers(countNumAlive(*file));

      gruppi = creaGruppiSvolgimento(file, numGruppi);
      printf("\nGRUPPI SVOLGIMENTO\n\n");
      printGruppi(gruppi, numGruppi);
      enter();

      for (i = ZERO; i < numGruppi; i++)
      {
        switch(gioco)
        {
          case PARIDISPARI:
            pariDispari(file, gruppi[i]);
            break;

          case DADI:
            dadi(file, gruppi[i]);
            break;

          case MORRACINESE:
            morraCinese(file, gruppi[i]);
            break;

          case TRIS:
            tris(file, gruppi[i]);
            break;

          case MURRA:
            murra(file, gruppi[i]);
            break;

          case BIGLIE:
            biglie(file, gruppi[i]);
            break;

          case IMPICCATO:
            impiccato(file, gruppi[i]);
            break;

          default:
            exit(NEG_VAL);
        }
      }

      free(gruppi);

      sceltaSalvataggio(*file);
    } while (countNumAlive(*file) != DUE_PLAYER);
  }
}