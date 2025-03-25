cmake_minimum_required(VERSION 3.22)
project(ProgettoFinale C)

set(CMAKE_C_STANDARD 90)

add_executable(
        ProgettoFinale main.c Utils/Utils.h Utils/Utils.c Fasi/Scrematura/Scrematura.c
        Fasi/Scrematura/Scrematura.h Giochi/MorraCinese/MorraCinese.c Giochi/MorraCinese/MorraCinese.h
        Giochi/Murra/Murra.c Giochi/Murra/Murra.h Giochi/PariDispari/PariDispari.c Giochi/PariDispari/PariDispari.h
        Giochi/Dadi/Dadi.c Giochi/Dadi/Dadi.h Giochi/Biglie/Biglie.c Giochi/Biglie/Biglie.h Fasi/Svolgimento/Svolgimento.c
        Fasi/Svolgimento/Svolgimento.h Fasi/Finale/Finale.c Fasi/Finale/Finale.h Fasi/Inizio.c Giochi/Giochi.h Fasi/Fasi.h
        Giochi/Impiccato/Impiccato.c Giochi/Impiccato/Impiccato.h Giochi/Tris/Tris.c Giochi/Tris/Tris.h)

