#include "Impiccato.h"

char *selectRigaFile(int r, char *nome_file)
{
  FILE *f = fopen(nome_file,"r");
  char *str = malloc(sizeof(char) * MAX_LEN_RIGA);
  int i = ZERO;

  if(f != NULL)
  {
    while(fgets(str, MAX_LEN_RIGA, f) != NULL && i < r)
      i++;

    fclose(f);
  }

  return str;
}

int numRigheFile(char *nome_file)
{
  FILE *f = fopen(nome_file,"r");
  char *str = malloc(sizeof(char) * MAX_RIGHE);
  int i = ZERO;

  if(f != NULL)
  {
    while (fgets(str,MAX_RIGHE, f))
      i++;
    fclose(f);
  }

  return i;
}

void initSegreta(char *str, char *segreta)
{
  int i;

  for(i = ZERO; i < strlen(str); i++)
  {
    if((str[i] > LETTERA_A_MIN && str[i] < LETTERA_Z_MIN) || (str[i] > LETTERA_A_MAIUSC && str[i] < LETTERA_Z_MAIUSC))
      segreta[i] = '_';
    else
      segreta[i] = str[i];
  }
}

bool isLetteraCorretta(char *str, char l)
{
  int i;

  for(i = ZERO; i < strlen(str); i++)
  {
    if(str[i] == l)
      return true;
  }

  return false;
}

void sostituisciLettera(char *segreta, char *str, char l)
{
  int i;

  for(i = ZERO; i < strlen(str); i++)
  {
    if(str[i] == l)
      segreta[i] = l;
  }
}

bool isFrase(char *str, char *segreta)
{
  int i;

  for(i = ZERO; i < strlen(str); i++)
    if(str[i] != segreta[i])
      return false;

  return true;
}

void initTentativi(int tentativi[QUATTRO_PLAYER])
{
  int i;

  for(i = ZERO; i < QUATTRO_PLAYER; i++)
    tentativi[i] = NUM_TENTATIVI;
}

bool isTentativiFiniti(int tentativi[QUATTRO_PLAYER])
{
  int i;

  for(i = ZERO; i < QUATTRO_PLAYER; i++)
    if(tentativi[i] > ZERO)
      return false;

  return true;
}

int impiccato(GameFile *file, Gruppo gruppo)
{
  int winner = NEG_VAL, num, i, j, tentativi[QUATTRO_PLAYER];
  char *str, *str_segreta, *temp;
  char lettera;

  str = malloc(sizeof(char) * MAX_LEN_RIGA);
  str_segreta = malloc(sizeof(char) * MAX_LEN_RIGA);

  system("cls");
  printf("----- IMPICCATO -----\n\n");

  if(cpuOnlyGruppo(*file, gruppo) == true)
  {
    num = rand() % gruppo.numGiocatori;
    winner = gruppo.giocatori[num];
  }

  else
  {
    num = rand() % numRigheFile(DEFAULT_DICTIONARY);
    str = selectRigaFile(num,DEFAULT_DICTIONARY);

    for(i = ZERO; i < strlen(str); i++)
      str[i] = tolower(str[i]);

    initSegreta(str,str_segreta);
    initTentativi(tentativi);

    while (winner == NEG_VAL)
    {
      i = ZERO;
      printf("\n___________________________\n\n");

      while(i < QUATTRO_PLAYER && winner == NEG_VAL)
      {
        if (tentativi[i] > ZERO)
        {
          for(j = ZERO; j < strlen(str); j++)
            printf("%c", str_segreta[j]);
          printf("\n");

          printf("\n\nScelta player %d: ", gruppo.giocatori[i]);

          if (isCpu(*file, gruppo.giocatori[i]))
          {
            lettera = LETTERA_A_MIN + rand() % (LETTERA_Z_MIN - LETTERA_A_MIN) + UNO;
            printf("%c\n", lettera);
          }

          else
          {
            do
            {
              scanf("%c", &lettera);
              getchar();
            } while(lettera < LETTERA_A_MIN || lettera > LETTERA_Z_MIN);
          }

          if (isLetteraCorretta(str, lettera))
          {
            sostituisciLettera(str_segreta, str, lettera);
            printf("Hai indovinato la lettera\n\n");
            sleep(UNO);

            if (isFrase(str, str_segreta))
              winner = gruppo.giocatori[i];
          }

          else
          {
            tentativi[i]--;

            if(isTentativiFiniti(tentativi) && winner == NEG_VAL)
            {
              printf("\nSei l'ultimo giocatore ad aver perso %d\n",gruppo.giocatori[i]);
              winner = gruppo.giocatori[i];
            }
          }

          printf("Hai %d tentativi\n", tentativi[i]);
          printf("-------------------------\n\n");
        }

        i++;
      }
    }
  }

  if(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali)!=NEG_VAL)
    if(isPlayerInGroup(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali),gruppo.giocatori,gruppo.numGiocatori)!=NEG_VAL)
      winner = gruppo.giocatori[isPlayerInGroup(searchName(NAME_IMMORTAL_PLAYER,file->giocatori,file->numRealGiocatoriTotali),gruppo.giocatori,gruppo.numGiocatori)];

  printf("\n\n\nHAI VINTO Giocatore n.%d\n\n", winner);
  enter();

  aggiornaStats(file, gruppo, winner, false);
  uccidiPlayer(file, gruppo, winner);

  free(str);
  free(str_segreta);

  return winner;
}