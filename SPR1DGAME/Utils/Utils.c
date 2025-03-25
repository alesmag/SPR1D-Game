#include "Utils.h"

int searchName(char *name, Giocatore *giocatori, int dim)
{
  int i;

  for(i = ZERO; i < dim; i++)
    if(strcmp(giocatori[i].nome,name) == ZERO)
      return giocatori[i].idGiocatore;

  return NEG_VAL;
}

int isPlayerInGroup(int id, int *array_id, int dim)
{
  int j;

    for(j = ZERO; j < dim; j++)
      if(id == array_id[j])
        return j;

  return NEG_VAL;
}

bool yesOrNo()
{
  char scelta[DUE];

  do
  {
    printf("\nScelta [y/n]: ");
    scanf("%s", scelta);
  } while ((strstr(scelta, "y") == NULL) && (strstr(scelta, "n") == NULL) && (strstr(scelta, "Y") == NULL) && (strstr(scelta, "N") == NULL));
  printf("\n");

  if((strcmp(scelta, "y") == ZERO) || (strcmp(scelta, "Y") == ZERO))
    return true;
  else
    return false;
}

void enter()
{
  printf("\n\nPremere INVIO per continuare\n");
  fflush(stdin);
  fflush(stdout);
  getchar();
}

bool cpuOnlyGruppo(GameFile file, Gruppo gruppo)
{
  int i;

  for(i = ZERO; i < gruppo.numGiocatori; i++)
    if(isCpu(file, gruppo.giocatori[i]) == false)
      return false;

  return true;
}

bool isCpu(GameFile file, int giocatoreGruppo)
{
  int i;

  for(i = ZERO; i < file.numRealGiocatoriAttuali; i++)
    if(file.giocatori[i].idGiocatore == giocatoreGruppo)
      return false;

  return true;
}

void stampaGiocatore(Giocatore giocatori)
{
  printf("ID Giocatore: %d\n", giocatori.idGiocatore);
  printf("Nome Giocatore: %s\n", giocatori.nome);
  printf("Totale giochi giocati: %d\n", giocatori.totaleGiochiGiocati);
  printf("Totale giochi vinti: %d\n", giocatori.totaleGiochiVinti);
  printf("Totale SPR1DGAME giocati: %d\n", giocatori.numSPR1DGiocati);
  printf("Totale finali giocate: %d\n", giocatori.numFinaliGiocate);
  printf("Totale SPR1DGAME vinti: %d\n", giocatori.numSPR1DVinti);
  printf("\n\n");
}

void stampaGiocatori(Giocatore *giocatori, int size)
{
  int i;

  for(i = ZERO; i < size; i++)
    stampaGiocatore(giocatori[i]);
}

void salvaFile(GameFile file, char *filename)
{
  FILE* f = fopen(filename, "wb");
  int i;

  if (f == NULL)
  {
    printf("\"%s\" non trovato. Utilizzo il file di default.\n", filename);
    fopen(DEFAULTSAVE, "wb");
  }

  fwrite(&file.numRealGiocatoriTotali,sizeof(int),UNO,f);

  for(i = ZERO; i < file.numRealGiocatoriTotali; i++)
  {
    fwrite(&file.giocatori[i].idGiocatore,sizeof(int),UNO,f);
    fwrite(&file.giocatori[i].nome,sizeof(char),MAX_LEN_NOME,f);
    fwrite(&file.giocatori[i].numSPR1DVinti,sizeof(int),UNO,f);
    fwrite(&file.giocatori[i].numSPR1DGiocati,sizeof(int),UNO,f);
    fwrite(&file.giocatori[i].numFinaliGiocate,sizeof(int),UNO,f);
    fwrite(&file.giocatori[i].totaleGiochiGiocati,sizeof(int),UNO,f);
    fwrite(&file.giocatori[i].totaleGiochiVinti,sizeof(int),UNO,f);
  }

  fwrite(&file.isInCorso,sizeof(int),UNO,f);

  if(file.isInCorso == true)
  {
    fwrite(&file.numGiocatoriTotali,sizeof(int),UNO,f);
    fwrite(&file.numRealGiocatoriAttuali,sizeof(int),UNO,f);

    for(i = ZERO; i < file.numRealGiocatoriAttuali; i++)
      fwrite(&file.indexGiocatori[i],sizeof(int),UNO,f);

    for(i = ZERO; i < file.numGiocatoriTotali; i++)
      fwrite(&file.inGioco[i],sizeof(int),UNO,f);
  }

  fclose(f);
}

GameFile caricaFile(char *filename)
{
  GameFile file;
  FILE* f = fopen(filename, "rb");
  int i;

  if (f == NULL)
    f = fopen(DEFAULTSAVE, "rb");

  fread(&file.numRealGiocatoriTotali,sizeof(int),UNO,f);
  file.giocatori = malloc(sizeof(Giocatore) * file.numRealGiocatoriTotali);

  for(i = ZERO; i < file.numRealGiocatoriTotali; i++)
  {
    fread(&file.giocatori[i].idGiocatore,sizeof(int),UNO,f);
    fread(&file.giocatori[i].nome,sizeof(char),MAX_LEN_NOME,f);
    fread(&file.giocatori[i].numSPR1DVinti,sizeof(int),UNO,f);
    fread(&file.giocatori[i].numSPR1DGiocati,sizeof(int),UNO,f);
    fread(&file.giocatori[i].numFinaliGiocate,sizeof(int),UNO,f);
    fread(&file.giocatori[i].totaleGiochiGiocati,sizeof(int),UNO,f);
    fread(&file.giocatori[i].totaleGiochiVinti,sizeof(int),UNO,f);
  }

  fread(&file.isInCorso,sizeof(int),UNO,f);

  if(file.isInCorso == true)
  {
    fread(&file.numGiocatoriTotali,sizeof(int),UNO,f);
    fread(&file.numRealGiocatoriAttuali,sizeof(int),UNO,f);

    file.indexGiocatori = malloc(sizeof (int) * file.numRealGiocatoriAttuali);

    for(i = ZERO; i < file.numRealGiocatoriAttuali; i++)
      fread(&file.indexGiocatori[i],sizeof(int),UNO,f);

    file.inGioco = malloc(sizeof(int) * file.numGiocatoriTotali);

    for(i = ZERO; i < file.numGiocatoriTotali; i++)
      fread(&file.inGioco[i], sizeof(int), UNO, f);
  }

  fclose(f);

  return file;
}

int numGruppiPlayers(int size)
{
  int esp = START_ESPONENTE, num;
  bool cond = true;

  while(cond == true)
  {
    num = pow(BASE, esp);

    if(num >= size)
      cond = false;
    else
      esp++;
  }

  return pow(BASE, esp - OFFSET_ESPONENTE);
}

void uccidiPlayer(GameFile *file, Gruppo gruppo, int winner)
{
  int i, posGiocatore;

  for(i = ZERO; i < gruppo.numGiocatori; i++)
  {
    if(gruppo.giocatori[i] != winner)
    {
      if(file->numRealGiocatoriAttuali != ZERO)
      {
        posGiocatore = findPosGiocatore(*file, gruppo.giocatori[i]);
        file->giocatori[posGiocatore].numSPR1DGiocati += UNO;
      }

      file->inGioco[gruppo.giocatori[i]] = DEAD;
    }
  }
}

int countNumAlive(GameFile file)
{
  int i, alive = ZERO;

  for(i = ZERO; i < file.numGiocatoriTotali; i++)
    if (file.inGioco[i] == ALIVE)
      alive++;

  return alive;
}

void alivePlayers(GameFile file, int *idNumAlive)
{
  int i, j = ZERO;

  for(i = ZERO; i < file.numGiocatoriTotali; i++)
  {
    if(file.inGioco[i] == ALIVE)
    {
      idNumAlive[j] = i;
      j++;
    }
  }
}

void printGruppi(Gruppo *gruppi, int numGruppi)
{
  int i, j;

  for(i = ZERO; i < numGruppi; i++)
  {
    printf("Gruppo %d: %d\n", i+UNO, gruppi[i].numGiocatori);

    for(j = ZERO; j < gruppi[i].numGiocatori; j++)
      printf("ID: %d\n", gruppi[i].giocatori[j]);
    printf("\n");
  }
}

void sceltaSalvataggio(GameFile file)
{
  char *name;
  bool scelta;

  name = malloc(sizeof(char) * MAX_LEN_NOME);

  printf("\n\nSalvare il gioco?");
  scelta = yesOrNo();
  printf("\n");

  if(scelta == true)
  {
    printf("Inserire il nome del file da salvare: ");
    scanf("%s", name);
    printf("\n");
    strcat(name, ".bin");

    salvaFile(file, name);
  }
}

char *sceltaCaricamento()
{
  FILE *f;
  char *name;

  name = malloc(sizeof(char) * MAX_LEN_NOME);

  do
  {
    printf("Inserire il nome del file da caricare: ");
    scanf("%s", name);
    printf("\n");
    strcat(name, ".bin");

    f = fopen(name,"rb");
  } while(f == NULL);

  return name;
}

int findPosGiocatore(GameFile file, int giocatore)
{
  int i;

  for(i = ZERO; i < file.numRealGiocatoriTotali; i++)
    if(file.giocatori[i].idGiocatore == giocatore)
      return i;

  return NEG_VAL;
}

void aggiornaStats(GameFile *file, Gruppo gruppo, int winner, bool isFinale)
{
  int posGiocatore, i;

  for(i = ZERO; i < gruppo.numGiocatori; i++)
  {
    if(isCpu(*file, gruppo.giocatori[i]) == false)
    {
      posGiocatore = findPosGiocatore(*file, gruppo.giocatori[i]);

      file->giocatori[posGiocatore].totaleGiochiGiocati += UNO;

      if(gruppo.giocatori[i] == winner)
      {
        file->giocatori[posGiocatore].totaleGiochiVinti += UNO;

        if(isFinale == true)
        {
          file->giocatori[posGiocatore].numFinaliGiocate += UNO;
          file->giocatori[posGiocatore].numSPR1DVinti += UNO;
          file->giocatori[posGiocatore].numSPR1DGiocati += UNO;
        }
      }

      else
      {
        if(isFinale == true)
          file->giocatori[posGiocatore].numFinaliGiocate += UNO;
      }
    }
  }
}

void resetGamefile(GameFile *file)
{
  int i;

  for(i = ZERO; i < file->numRealGiocatoriTotali; i++)
    file->giocatori[i].idGiocatore = NEG_VAL;

  file->isInCorso = false;
}