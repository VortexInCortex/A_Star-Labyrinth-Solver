cmake_minimum_required(VERSION 3.29)
project(Fichiers_fournis_TP_1_20241108 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Fichiers_fournis_TP_1_20241108
    couleurs.c
    couleurs.h
    labyrinthe.c
    labyrinthe.h
    liste.c
    liste.h
    main.c
    menu.c
    menu.h
    noeud.c
    noeud.h)
