#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jeu.h"
#include "liste.h"

static void afficher_entete(void) {
    printf("\n========================================\n");
    printf("        JEU DE LA BATAILLE v1.0         \n");
    printf("========================================\n");
}

const char *nom_valeur(int valeur) {
    switch (valeur) {
        case 11: return "Valet";
        case 12: return "Dame";
        case 13: return "Roi";
        case 14: return "As";
        default: {
            static char buffer[3][4];
            static int index = 0;
            index = (index + 1) % 3;
            snprintf(buffer[index], sizeof(buffer[index]), "%d", valeur);
            return buffer[index];
        }
    }
}

static void afficher_score(const Jeu *jeu) {
    printf("Score -> J1: %d cartes | J2: %d cartes\n",
           taille_file(&jeu->joueur1), taille_file(&jeu->joueur2));
}

static int joueur_gagnant_duel(Carte *c1, Carte *c2) {
    if (c1->valeur > c2->valeur) {
        return 1;
    }
    if (c2->valeur > c1->valeur) {
        return 2;
    }
    return 0;
}

static int resoudre_bataille(Jeu *jeu, PileCartes *zone, Carte *carte1_visible, Carte *carte2_visible) {
    int gagnant = joueur_gagnant_duel(carte1_visible, carte2_visible);

    while (gagnant == 0) {
        Carte *cachee1;
        Carte *cachee2;
        Carte *visible1;
        Carte *visible2;

        printf(" >>> BATAILLE ! Chaque joueur pose 1 carte cachee et 1 carte visible.\n");

        if (file_vide(&jeu->joueur1)) {
            printf("Joueur 1 ne peut plus continuer la bataille.\n");
            return 2;
        }
        if (file_vide(&jeu->joueur2)) {
            printf("Joueur 2 ne peut plus continuer la bataille.\n");
            return 1;
        }

        cachee1 = defiler(&jeu->joueur1);
        cachee2 = defiler(&jeu->joueur2);
        empiler(zone, cachee1);
        empiler(zone, cachee2);
        printf("    Les cartes cachees ont ete posees.\n");

        if (file_vide(&jeu->joueur1)) {
            printf("Joueur 1 n'a plus de carte visible a jouer.\n");
            return 2;
        }
        if (file_vide(&jeu->joueur2)) {
            printf("Joueur 2 n'a plus de carte visible a jouer.\n");
            return 1;
        }

        visible1 = defiler(&jeu->joueur1);
        visible2 = defiler(&jeu->joueur2);
        empiler(zone, visible1);
        empiler(zone, visible2);

        printf("Joueur 1 decouvre : [%s de %s]\n", nom_valeur(visible1->valeur), visible1->couleur);
        printf("Joueur 2 decouvre : [%s de %s]\n", nom_valeur(visible2->valeur), visible2->couleur);

        gagnant = joueur_gagnant_duel(visible1, visible2);
    }

    return gagnant;
}

void initialiser_jeu(Jeu *jeu, int max_tours) {
    Carte *paquet;
    int i;

    if (jeu == NULL) {
        return;
    }

    initialiser_file(&jeu->joueur1);
    initialiser_file(&jeu->joueur2);
    jeu->tours_joues = 0;
    jeu->max_tours = max_tours;

    srand((unsigned int)time(NULL));

    paquet = creer_paquet_standard();
    if (paquet == NULL) {
        fprintf(stderr, "Erreur critique : impossible de creer le paquet.\n");
        exit(EXIT_FAILURE);
    }

    melanger_liste(&paquet);

    for (i = 0; i < 26; i++) {
        enfiler(&jeu->joueur1, retirer_tete_liste(&paquet));
        enfiler(&jeu->joueur2, retirer_tete_liste(&paquet));
    }

    liberer_liste(&paquet);
}

void jouer_partie(Jeu *jeu) {
    afficher_entete();

    while (!file_vide(&jeu->joueur1) && !file_vide(&jeu->joueur2) && jeu->tours_joues < jeu->max_tours) {
        Carte *carte1;
        Carte *carte2;
        PileCartes zone_bataille;
        int gagnant;

        initialiser_pile(&zone_bataille);
        jeu->tours_joues++;

        printf("\n--- MANCHE %d ---\n", jeu->tours_joues);

        carte1 = defiler(&jeu->joueur1);
        carte2 = defiler(&jeu->joueur2);

        if (carte1 == NULL || carte2 == NULL) {
            free(carte1);
            free(carte2);
            break;
        }

        printf("Joueur 1 joue : [%s de %s] (valeur = %d)\n",
               nom_valeur(carte1->valeur), carte1->couleur, carte1->valeur);
        printf("Joueur 2 joue : [%s de %s] (valeur = %d)\n",
               nom_valeur(carte2->valeur), carte2->couleur, carte2->valeur);

        empiler(&zone_bataille, carte1);
        empiler(&zone_bataille, carte2);

        gagnant = resoudre_bataille(jeu, &zone_bataille, carte1, carte2);

        if (gagnant == 1) {
            printf(" >>> Joueur 1 remporte la manche ! (+%d cartes)\n", taille_pile(&zone_bataille));
            vider_pile_dans_file(&zone_bataille, &jeu->joueur1);
        } else {
            printf(" >>> Joueur 2 remporte la manche ! (+%d cartes)\n", taille_pile(&zone_bataille));
            vider_pile_dans_file(&zone_bataille, &jeu->joueur2);
        }

        afficher_score(jeu);
    }

    printf("\n========================================\n");
    printf("Fin de la partie apres %d tours.\n", jeu->tours_joues);

    if (taille_file(&jeu->joueur1) > taille_file(&jeu->joueur2)) {
        printf("Vainqueur : Joueur 1\n");
    } else if (taille_file(&jeu->joueur2) > taille_file(&jeu->joueur1)) {
        printf("Vainqueur : Joueur 2\n");
    } else {
        printf("Resultat : Egalite (max de tours atteint).\n");
    }

    afficher_score(jeu);
    printf("========================================\n");
}

void liberer_jeu(Jeu *jeu) {
    if (jeu == NULL) {
        return;
    }

    liberer_file(&jeu->joueur1);
    liberer_file(&jeu->joueur2);
}
