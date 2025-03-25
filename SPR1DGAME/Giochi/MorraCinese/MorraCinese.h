#include "../../Utils/Utils.h"

#ifndef PROGETTOFINALE_MORRACINESE_H
#define PROGETTOFINALE_MORRACINESE_H

typedef enum {CARTA, FORBICI, SASSO} segno;

// permette alla cpu di selezionare casualmente il segno che giocherà
void sceltaCpuMorraCinese(int *scelta, Gruppo gruppo, int i);

// permette al giocatore di selezionare il segno che vuole giocare
void sceltaGiocatoreMorraCinese(int *scelta, Gruppo gruppo, int i);

// gioco della morra cinese (carta, forbici, sasso)
int morraCinese(GameFile *file, Gruppo gruppo);

#endif //PROGETTOFINALE_MORRACINESE_H