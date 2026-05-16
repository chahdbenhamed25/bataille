#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "liste.h"
#include "jeu.h"

Carte *creer_carte(int valeur, const char *couleur) {
    Carte *carte = (Carte *)malloc(sizeof(Carte));
    if (carte == NULL) {
        fprintf(stderr, "Erreur : allocation memoire impossible pour une carte.\n");
        return NULL;
    }

    carte->valeur = valeur;
    strncpy(carte->couleur, couleur, TAILLE_COULEUR - 1);
    carte->couleur[TAILLE_COULEUR - 1] = '\0';
    carte->suivant = NULL;
    return carte;
}

void inserer_tete_liste(Carte **tete, Carte *nouvelle_carte) {
    if (tete == NULL || nouvelle_carte == NULL) {
        return;
    }

    nouvelle_carte->suivant = *tete;
    *tete = nouvelle_carte;
}

void inserer_fin_liste(Carte **tete, Carte *nouvelle_carte) {
    Carte *courant;

    if (tete == NULL || nouvelle_carte == NULL) {
        return;
    }

    nouvelle_carte->suivant = NULL;

    if (*tete == NULL) {
        *tete = nouvelle_carte;
        return;
    }

    courant = *tete;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouvelle_carte;
}

Carte *retirer_tete_liste(Carte **tete) {
    Carte *retiree;

    if (tete == NULL || *tete == NULL) {
        return NULL;
    }

    retiree = *tete;
    *tete = (*tete)->suivant;
    retiree->suivant = NULL;
    return retiree;
}

int taille_liste(const Carte *tete) {
    int compteur = 0;
    const Carte *courant = tete;

    while (courant != NULL) {
        compteur++;
        courant = courant->suivant;
    }

    return compteur;
}

void afficher_liste(const Carte *tete) {
    const Carte *courant = tete;

    while (courant != NULL) {
        printf("[%s de %s] -> ", nom_valeur(courant->valeur), courant->couleur);
        courant = courant->suivant;
    }
    printf("NULL\n");
}

void liberer_liste(Carte **tete) {
    Carte *courant;
    Carte *suivant;

    if (tete == NULL) {
        return;
    }

    courant = *tete;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
    *tete = NULL;
}

Carte *creer_paquet_standard(void) {
    int valeur;
    int i;
    const char *couleurs[] = {"Coeur", "Carreau", "Trefle", "Pique"};
    Carte *paquet = NULL;

    for (i = 0; i < 4; i++) {
        for (valeur = 2; valeur <= 14; valeur++) {
            Carte *carte = creer_carte(valeur, couleurs[i]);
            if (carte == NULL) {
                liberer_liste(&paquet);
                return NULL;
            }
            inserer_fin_liste(&paquet, carte);
        }
    }

    return paquet;
}

void melanger_liste(Carte **tete) {
    int i;
    int j;
    int n;
    Carte **tableau;

    if (tete == NULL || *tete == NULL) {
        return;
    }

    n = taille_liste(*tete);
    if (n < 2) {
        return;
    }

    tableau = (Carte **)malloc((size_t)n * sizeof(Carte *));
    if (tableau == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer le tableau temporaire de melange.\n");
        return;
    }

    {
        Carte *courant = *tete;
        for (i = 0; i < n; i++) {
            tableau[i] = courant;
            courant = courant->suivant;
        }
    }

    for (i = n - 1; i > 0; i--) {
        Carte *temp;
        j = rand() % (i + 1);
        temp = tableau[i];
        tableau[i] = tableau[j];
        tableau[j] = temp;
    }

    for (i = 0; i < n - 1; i++) {
        tableau[i]->suivant = tableau[i + 1];
    }
    tableau[n - 1]->suivant = NULL;
    *tete = tableau[0];

    free(tableau);
}
