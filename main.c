/* Nome: Alessio Giuseppe Muggittu
 * Matricola: 60/61/66124
 */

#include "Utils/Utils.h"
#include "Fasi/Fasi.h"

int main()
{
  GameFile file;
  Gruppo *gruppi;
  int scelta, i, numGruppi;
  char *name;

  srand(time(NULL));

  do
  {
    system("cls");

    do
    {
      printf("Scegliere se caricare un file o iniziare una nuova partita \n1: Caricare un file \n2: Nuova partita \nScelta: ");
      scanf("%d", &scelta);
      printf("\n");
    } while(scelta < UNO || scelta > DUE);

    if(scelta == DUE)
    {
      inizio(&file);
      sceltaSalvataggio(file);
    }

    else
    {
      name = sceltaCaricamento();
      file = caricaFile(name);

      if(file.isInCorso == false)
      {
        system("cls");
        file.numGiocatoriTotali = numGiocatori();
        file.isInCorso = true;
        abilitaGiocatori(&file);
        assegnaGiocatori(&file);

        numGruppi = numGruppiPlayers(file.numGiocatoriTotali);
        gruppi = creaGruppiIniziali(&file, numGruppi);

        for(i = ZERO; i < numGruppi; i++)
        {
          system("cls");
          scrematura(&file, gruppi[i]);
        }

        sceltaSalvataggio(file);

        free(gruppi);
      }
    }

    svolgimento(&file);
    finale(&file);
    resetGamefile(&file);
    sceltaSalvataggio(file);

    printf("\n--- STATISTICHE GIOCATORI ---\n\n");
    stampaGiocatori(file.giocatori, file.numRealGiocatoriTotali);

    free(file.inGioco);
    free(file.giocatori);

    printf("\nRigiocare?");
  } while(yesOrNo());

  return 0;
}