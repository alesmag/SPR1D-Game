#include "../../Utils/Utils.h"

#ifndef PROGETTOFINALE_DADI_H
#define PROGETTOFINALE_DADI_H

// permette al giocatore di premere invio per lanciare casualmente i dati, la cpu invece li tirerà automaticamente al proprio turno
int lanciaDadi(GameFile *file, Gruppo gruppo, int i);

// gioco dei dadi
int dadi(GameFile *file, Gruppo gruppo);

#endif //PROGETTOFINALE_DADI_H
