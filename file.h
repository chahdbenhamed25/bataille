#ifndef FILE_H
#define FILE_H

#include "carte.h"

typedef struct {
    Carte *tete;
    Carte *queue;
    int taille;
} FileCartes;

void initialiser_file(FileCartes *file);
int file_vide(const FileCartes *file);
int taille_file(const FileCartes *file);
void enfiler(FileCartes *file, Carte *carte);
Carte *defiler(FileCartes *file);
void afficher_file(const FileCartes *file);
void liberer_file(FileCartes *file);

#endif
