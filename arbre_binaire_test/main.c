/*

    Copyright (c) 2019 Olivier Meloche

    L'autorisation est accordée, gracieusement, à toute personne acquérant une
    copie de cette bibliothèque et des fichiers de documentation associés
    (la "Bibliothèque"), de commercialiser la Bibliothèque sans restriction,
    notamment les droits d'utiliser, de copier, de modifier, de fusionner, de
    publier, de distribuer, de sous-licencier et / ou de vendre des copies de
    la Bibliothèque, ainsi que d'autoriser les personnes auxquelles la
    Bibliothèque est fournie à le faire, sous réserve des conditions suivantes:

    La déclaration de copyright ci-dessus et la présente autorisation doivent
    être incluses dans toutes copies ou parties substantielles de la
    Bibliothèque.

    LA BIBLIOTHÈQUE EST FOURNIE "TELLE QUELLE", SANS GARANTIE D'AUCUNE SORTE,
    EXPLICITE OU IMPLICITE, NOTAMMENT SANS GARANTIE DE QUALITÉ MARCHANDE,
    D’ADÉQUATION À UN USAGE PARTICULIER ET D'ABSENCE DE CONTREFAÇON. EN AUCUN
    CAS, LES AUTEURS OU TITULAIRES DU DROIT D'AUTEUR NE SERONT RESPONSABLES DE
    TOUT DOMMAGE, RÉCLAMATION OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS LE
    CADRE D'UN CONTRAT, D'UN DÉLIT OU AUTRE, EN PROVENANCE DE, CONSÉCUTIF À OU
    EN RELATION AVEC LA BIBLIOTHÈQUE OU SON UTILISATION, OU AVEC D'AUTRES
    ÉLÉMENTS DE LA BIBLIOTHÈQUE.

*/

/**
 *  \file main.c
 *
 *  Effectue les testes de l'arbre binaire.
 *
 */

#include "arbre_binaire.h"

/**
  * \brief Affiche tous les noeuds
  *
  * \param arbre L'arbre désiré
  */
void afficher_arbre_binaire(arbre_binaire* arbre) {
    if (arbre != NULL){
        printf("%d\n", element_arbre_binaire(arbre));
        if (enfant_gauche_arbre_binaire(arbre) != NULL) {
            afficher_arbre_binaire(enfant_gauche_arbre_binaire(arbre));
        }
        if (enfant_droit_arbre_binaire(arbre) != NULL){
            afficher_arbre_binaire(enfant_droit_arbre_binaire(arbre));
        }
    }
}

/**
 * \brief Teste de l'arbre binaire
 */
int main(void) {
  int i = 0, j = 0, k = 0, l = 0, m = 0, nombre = 0;
  bool n;
  arbre_binaire* test1;
  arbre_binaire* test2;
  arbre_binaire* gauche;
  arbre_binaire* droit;
  printf("[DEBUT DU TEST]\n");

  test1 = creer_arbre_binaire(69);
  if (test1) {
    printf("Arbre Binaire 'test1' cree.\n\n");

    i = element_arbre_binaire(test1);
    printf("ELEMENT: %d\n", i); /// <69

    creer_enfant_gauche_arbre_binaire(test1, 70);

    creer_enfant_droit_arbre_binaire(test1, 170);
    creer_enfant_droit_arbre_binaire(test1, 170); /// <Erreur
    if (a_erreur_arbre_binaire(test1)) {
      printf("Erreur: %s\n", erreur_arbre_binaire(test1));
    }

    gauche = enfant_gauche_arbre_binaire(test1);
    creer_enfant_gauche_arbre_binaire(gauche, 71);
    gauche = enfant_gauche_arbre_binaire(gauche);
    creer_enfant_gauche_arbre_binaire(gauche, 72);
    creer_enfant_droit_arbre_binaire(gauche, 73);

    droit = enfant_droit_arbre_binaire(test1);
    creer_enfant_gauche_arbre_binaire(droit, 171);
    creer_enfant_droit_arbre_binaire(droit, 172);

    k = nombre_feuilles_arbre_binaire(test1);
    printf("FEUILLE: %d\n", k);

    l = nombre_elements_arbre_binaire(test1);
    printf("NOEUD: %d\n", l);

    m = hauteur_arbre_binaire(test1);
    printf("HAUTEUR: %d\n", m);

    nombre = 73;
    n = contient_element_arbre_binaire(test1, nombre);
    if (n) {
      printf("L'element %d existe.\n", nombre);
    } else {
      printf("L'element %d n'existe pas.\n", nombre);
    }
    if (a_erreur_arbre_binaire(test1)) {
      printf("Erreur: %s\n", erreur_arbre_binaire(test1));
    }

    retirer_enfant_gauche_arbre_binaire(test1);
    retirer_enfant_gauche_arbre_binaire(droit);
    retirer_enfant_droit_arbre_binaire(droit); /// <Reste seulement 69, 170
    nombre = 171;
    n = contient_element_arbre_binaire(test1, nombre);
    if (n) {
      printf("L'element %d existe.\n", nombre);
    } else {
      printf("L'element %d n'existe pas.\n", nombre);
    }
    if (a_erreur_arbre_binaire(test1)) {
      printf("Erreur: %s\n", erreur_arbre_binaire(test1));
    }

    modifier_element_arbre_binaire(test1, 690);
    j = element_arbre_binaire(test1);
    printf("ELEMENT: %d\n", j); /// <69 devient 690

    sauvegarder_arbre_binaire(test1, "test1.bin");
    printf("Arbre Binaire 'test1' enregistre.\n");

    detruire_arbre_binaire(test1);
    printf("Arbre Binaire 'test1' detruit.\n\n");

    test2 = charger_arbre_binaire("test1.bin");
    if (test2) {
      printf("Arbre Binaire 'test2' cree.\n\n");
      afficher_arbre_binaire(test2); /// <690, 170

    } else {
      printf("'test2' Impossible de charger le fichier.\n");
    }
  } else {
    printf("'test1' Une erreur est survenue.\n");
  }
  return 0;
}
