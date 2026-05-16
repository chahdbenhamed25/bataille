#include <stdlib.h>

#include "pile.h"

void initialiser_pile(PileCartes *pile) {
    if (pile == NULL) {
        return;
    }

    pile->sommet = NULL;
    pile->taille = 0;
}

int pile_vide(const PileCartes *pile) {
    return (pile == NULL || pile->sommet == NULL);
}

int taille_pile(const PileCartes *pile) {
    if (pile == NULL) {
        return 0;
    }
    return pile->taille;
}

void empiler(PileCartes *pile, Carte *carte) {
    if (pile == NULL || carte == NULL) {
        return;
    }

    carte->suivant = pile->sommet;
    pile->sommet = carte;
    pile->taille++;
}

Carte *depiler(PileCartes *pile) {
    Carte *retiree;

    if (pile_vide(pile)) {
        return NULL;
    }

    retiree = pile->sommet;
    pile->sommet = pile->sommet->suivant;
    retiree->suivant = NULL;
    pile->taille--;
    return retiree;
}

void vider_pile_dans_file(PileCartes *pile, FileCartes *file_gagnant) {
    Carte *carte;

    if (pile == NULL || file_gagnant == NULL) {
        return;
    }

    while ((carte = depiler(pile)) != NULL) {
        enfiler(file_gagnant, carte);
    }
}

void liberer_pile(PileCartes *pile) {
    Carte *courant;

    if (pile == NULL) {
        return;
    }

    while ((courant = depiler(pile)) != NULL) {
        free(courant);
    }
}
