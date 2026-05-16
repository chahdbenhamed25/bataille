#include <stdio.h>

#include "jeu.h"

int main(void) {
    Jeu jeu;
    const int max_tours = 10000;

    initialiser_jeu(&jeu, max_tours);
    jouer_partie(&jeu);
    liberer_jeu(&jeu);

    return 0;
}
