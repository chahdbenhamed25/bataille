#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "jeu.h"

void initialiser_file(FileCartes *file) {
    if (file == NULL) {
        return;
    }

    file->tete = NULL;
    file->queue = NULL;
    file->taille = 0;
}

int file_vide(const FileCartes *file) {
    return (file == NULL || file->tete == NULL);
}

int taille_file(const FileCartes *file) {
    if (file == NULL) {
        return 0;
    }
    return file->taille;
}

void enfiler(FileCartes *file, Carte *carte) {
    if (file == NULL || carte == NULL) {
        return;
    }

    carte->suivant = NULL;

    if (file->queue == NULL) {
        file->tete = carte;
        file->queue = carte;
    } else {
        file->queue->suivant = carte;
        file->queue = carte;
    }

    file->taille++;
}

Carte *defiler(FileCartes *file) {
    Carte *retiree;

    if (file_vide(file)) {
        return NULL;
    }

    retiree = file->tete;
    file->tete = file->tete->suivant;

    if (file->tete == NULL) {
        file->queue = NULL;
    }

    retiree->suivant = NULL;
    file->taille--;
    return retiree;
}

void afficher_file(const FileCartes *file) {
    const Carte *courant;

    if (file == NULL) {
        return;
    }

    courant = file->tete;
    while (courant != NULL) {
        printf("[%s de %s] <- ", nom_valeur(courant->valeur), courant->couleur);
        courant = courant->suivant;
    }
    printf("FIN\n");
}

void liberer_file(FileCartes *file) {
    Carte *courant;

    if (file == NULL) {
        return;
    }

    while ((courant = defiler(file)) != NULL) {
        free(courant);
    }
}
