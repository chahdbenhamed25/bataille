#ifndef PILE_H
#define PILE_H

#include "carte.h"
#include "file.h"

typedef struct {
    Carte *sommet;
    int taille;
} PileCartes;

void initialiser_pile(PileCartes *pile);
int pile_vide(const PileCartes *pile);
int taille_pile(const PileCartes *pile);
void empiler(PileCartes *pile, Carte *carte);
Carte *depiler(PileCartes *pile);
void vider_pile_dans_file(PileCartes *pile, FileCartes *file_gagnant);
void liberer_pile(PileCartes *pile);

#endif
