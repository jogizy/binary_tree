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
 *  \file arbre_binaire.h
 *
 *  Fichier d'implémentation contenant la structure de donnée 'arbre_binaire'.
 *  Un arbre binaire est un un graphe connexe acyclique orienté dont tous les
 *  noeuds ont au maximum un parent et dont chaque noeuds peu avoir un maximum
 *  de 2 enfants.
 *
 */

#ifndef _arbre_h
#define _arbre_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ERREUR_TAILLE 255

/**
 * \brief Un arbre implémentée de structures liées
 */
typedef struct arbre_binaire_struct arbre_binaire;

/**
  * \brief Créer un nouvel arbre_binaire en assignant la `valeur' à sa racine.
  *
  * \param valeur La valeur qui sera assigné à la racine
  *
  * \return l'arbre binaire
  */
arbre_binaire* creer_arbre_binaire(int valeur);

/**
  * \brief Retourne un nouvel arbre_binaire.
  *
  * L'arbre est créé graçe aux données du fichier binaire `nom_fichier'.
  * Le fichier doit être créé à l'aide de la routine “sauvegarder_arbre_binaire”
  *
  * \param nom_fichier Le nom du fichier
  *
  * \return l'arbre binaire
  */
arbre_binaire* charger_arbre_binaire(char *nom_fichier);

/**
  * \brief Libère l'espace mémoire utilisé par l'arbre
  *  (libère également tous les enfants).
  *
  * \param arbre L'arbre à désalloué
  */
void detruire_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Sauvegarde l'arbre dans le fichier binaire `nom_fichier'
  *
  * \param arbre L'arbre à enregistrer
  * \param nom_fichier Le nom du fichier
  */
void sauvegarder_arbre_binaire(arbre_binaire* arbre, char * nom_fichier);

/**
  * \brief Retourne le nombre d'éléments contenus dans l'arbre.
  *
  * Corresponds également au nombre de noeuds de l'arbre.
  *
  * \param arbre L'arbre désiré
  *
  * \return Le nombre d'élément de l'arbre
  *
  * \note 'arbre' ne doit pas être NULL
  */
int nombre_elements_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Retourne le nombre de feuilles de l'arbre.
  *
  * Une feuille correspond à un noeud n'ayant AUCUN enfant.
  *
  * \param arbre L'arbre désiré
  *
  * \return Le nombre de feuille de l'arbre
  *
  * \note 'arbre' ne doit pas être NULL
  */
int nombre_feuilles_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Retourne la hauteur de l'arbre.
  *
  * \param arbre L'arbre désiré
  *
  * \return La hauteur de l'arbre
  */
int hauteur_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Retourne l'élément contenu dans la racine de l'arbre.
  *
  * \param arbre L'arbre désiré
  *
  * \return La valeur contenu dans la racine de l'arbre
  */
int element_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Remplace l'élément à la racine de l'arbre par `valeur'.
  *
  * \param arbre L'arbre désiré
  * \param valeur La nouvelle valeur
  */
void modifier_element_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
  * \brief Retourne vrai si l'arbre contient la `valeur'
  *
  * La `valeur' peut être contenue soit dans sa racine ou dans ces descendances.
  *
  * \param arbre L'arbre désiré
  * \param valeur La valeur recherché
  *
  * \return Vrai si la valeur recherché existe, sinon Faux.
  */
bool contient_element_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
  * \brief Retourne le sous-arbre enfant gauche de `arbre'.
  *
  * Retourne `NULL' si `arbre' n'a pas d’enfant gauche.
  *
  * \param arbre L'arbre désiré
  *
  * \return le sous-arbre enfant gauche
  */
arbre_binaire* enfant_gauche_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Créer l’enfant gauche de `arbre' et assigne `valeur' à sa racine.
  *
  * Si `arbre' a déjà un enfant gauche, ne change rien et retourne une erreur.
  *
  * \param arbre L'arbre désiré
  * \param valeur La valeur qui sera assigné à sa racine
  */
void creer_enfant_gauche_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
  * \brief Libère l’enfant gauche de `arbre'.
  *
  * \param arbre L'arbre désiré
  */
void retirer_enfant_gauche_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Retourne le sous-arbre enfant droit de `arbre'.
  *
  * Retourne `NULL' si `arbre' n'a pas d’enfant droit.
  *
  * \param arbre L'arbre désiré
  *
  * \return le sous-arbre enfant droit
  */
arbre_binaire* enfant_droit_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Créer l’enfant droit de `arbre' et assigne `valeur' à sa racine.
  *
  * Si `arbre' a déjà un enfant droit, ne change rien et retourne une erreur.
  *
  * \param arbre L'arbre désiré
  * \param valeur La valeur qui sera assigné à sa racine
  */
void creer_enfant_droit_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
  * \brief Libère l’enfant droit de `arbre'.
  *
  * \param arbre L'arbre désiré
  */
void retirer_enfant_droit_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Valide si une erreur est arrivée lors du dernier appel de fonction
  *  de la librairie.
  *
  * \param arbre L'arbre désiré
  *
  * \return Vrai si une erreur est arrivée, sinon Faux.
  */
bool a_erreur_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Si “a_erreur_arbre_binaire” est vrai, retourne une description de
  *  l'erreur.
  *
  * \param arbre L'arbre désiré
  *
  * \return La description de l'erreur.
  */
char* erreur_arbre_binaire(arbre_binaire* arbre);

/**
  * \brief Insert le message d'erreur dans l'arbre.
  *
  * Également, mets “a_erreur_arbre_binaire” à Vrai.
  * Une copie de l'erreur doit être gardée dans la librairie.
  *
  * \param arbre L'arbre désiré
  * \param erreur L'erreur à inscrire
  */
void inscrire_erreur_arbre_binaire(arbre_binaire* arbre, const char* erreur);

/**
  * \brief Met “a_erreur_arbre_binaire” à Faux.
  *
  * \param arbre L'arbre désiré
  */
void retirer_erreur_arbre_binaire(arbre_binaire* arbre);


#endif /* _arbre_h */
