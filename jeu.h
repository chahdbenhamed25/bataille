#ifndef JEU_H
#define JEU_H

#include "file.h"
#include "pile.h"

typedef struct {
    FileCartes joueur1;
    FileCartes joueur2;
    int tours_joues;
    int max_tours;
} Jeu;

void initialiser_jeu(Jeu *jeu, int max_tours);
void jouer_partie(Jeu *jeu);
void liberer_jeu(Jeu *jeu);
const char *nom_valeur(int valeur);

#endif
