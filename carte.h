#ifndef CARTE_H
#define CARTE_H

#define TAILLE_COULEUR 10

typedef struct Carte {
    int valeur;                  /* 2..14, As = 14 */
    char couleur[TAILLE_COULEUR];
    struct Carte *suivant;
} Carte;

#endif
