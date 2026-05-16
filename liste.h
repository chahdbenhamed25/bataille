#ifndef LISTE_H
#define LISTE_H

#include "carte.h"

Carte *creer_carte(int valeur, const char *couleur);
void inserer_tete_liste(Carte **tete, Carte *nouvelle_carte);
void inserer_fin_liste(Carte **tete, Carte *nouvelle_carte);
Carte *retirer_tete_liste(Carte **tete);
int taille_liste(const Carte *tete);
void afficher_liste(const Carte *tete);
void liberer_liste(Carte **tete);
Carte *creer_paquet_standard(void);
void melanger_liste(Carte **tete);

#endif
